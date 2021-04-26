#include <iostream>
#include <vector>

// 解法一：递归+去除重叠计算
int recMakeChange(std::vector<int>& coins, int amount, std::vector<int>& dp_table) {
    // 不能找零
    if (amount < 0) {
        return -1;
    // 完成找零
    }else if (amount == 0) {
        return 0;
     // 屏蔽重叠计算
    }else if (dp_table[amount] > 0) {
        return dp_table[amount];
    }else {
        int coin_count = amount;
        for(int i = 0; i < coins.size(); i ++) {
            int sub_coin_count = recMakeChange(coins, amount - coins[i], dp_table);
            if (sub_coin_count == -1) {
                continue;
            }
            coin_count = std::min(coin_count, sub_coin_count + 1);
        }
        dp_table[amount] = coin_count;
        return coin_count;
    }
}

int coinChange(std::vector<int>& coins, int amount) {
    if (amount < 0) {
        return -1;
    }else if (amount == 0) {
        return 0;
    }
    std::vector<int> dp_table = std::vector<int>(amount+1);
    int change_count = recMakeChange(coins, amount, dp_table);
    return change_count;
}

// 解法二：动态规划+去除重叠子问题
int dpCoinChange(std::vector<int>& coins, int amount) {
    if (amount < 0) {
        return -1;
    }else if (amount == 0) {
        return 0;
    }
    int dp_table[amount+1];
    // 自底向上计算最优子集，如果子集已经是最优解，那么基于子集计算的结果一定是最优解
    for(int change = 1; change <= amount; change++) {
        // 最优解的初始值是本身，即只由面值为1的硬币组成
        int min_coin_count = INT_MAX;
        // 开始找零
        for (int i = 0; i < coins.size(); i++) {
            // 判断当前面值是否能找零
            int sub_change = change - coins[i];
            // 当前面值不能找零或子集不能找零
            if (sub_change < 0 || dp_table[sub_change] == -1) {
                continue;
            }
            // 如果可以找零，那么当前面值的零钱数等于面值为sub_change的最小零钱数+1
            int coin_count = dp_table[sub_change] + 1;
            // 更新当前面值的最小零钱数
            if (coin_count < min_coin_count) {
                min_coin_count = coin_count;
            }
        }
        // 记录当前面值的最小零钱数
        dp_table[change] = min_coin_count == INT_MAX ? -1 : min_coin_count;
    }
    return dp_table[amount];
}

int main(int argc, const char * argv[]) {
	std::vector<int> coins = {1,2,5};
    int amount = 11;

	// 解法一
    // int change_count = coinChange(coins, amount);

    // 解法二
    int change_count = dpCoinChange(coins, amount);

    std::cout << "coinChange(" << amount << ") = " << change_count << std::endl;
	return 0;
}