/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

 

Example 1:
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

Example 2:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.
 

Constraints:

1 <= prices.length <= 105
0 <= prices[i] <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>

using namespace std;

// 题解一：动态规划思想，使用dp[i]表示地第i天可获得的最大利润，dp[i] = max(dp[i-1], 第i的卖出的利润) 
// 使用两个变量分别记录当前最低和最高股价，一旦遇到比当前更高的股价则更新利润值，一旦遇到更低的股价则同时更新当前最低值和最高值，等待更高的股价值
// 时间复杂度：O(n), 空间复杂度：O(1)
int maxProfit1(vector<int>& prices) {
	int n = prices.size();
	int last_buy = prices[0];
	int last_sell = prices[0];
	int profit = last_sell - last_buy;
	for (int i = 1; i < n; ++i) {
		if (prices[i] > last_sell) {
			last_sell = prices[i];
			// 由于last_buy也是动态更新的，因此每次last_sell更新时，profit的新值需要与旧值比较取二者较大值
			profit = max(profit, last_sell - last_buy);
		}else if (prices[i] < last_buy) {
			last_buy = prices[i];
			last_sell = last_buy;
		}
	}
	return profit;
}

int maxProfit(vector<int>& prices) {
	int n = prices.size();
	int min_buy = prices[0];
	int profit = 0;
	for (int i = 0; i < n; ++i)
	{
		min_buy = min(min_buy, prices[i]);
		profit = max(profit, prices[i] - min_buy);
	}
	return profit;
}

int main(int argc, const char* argv[]) {
	vector<int> prices = {7,1,5,3,6,4};
	// vector<int> prices = {7,6,4,3,1};
	cout << "max profit: " << maxProfit(prices) << endl;
	return 0;
}

