/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete at most two transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:
Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.


Example 2:
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.

Example 3:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
Example 4:

Input: prices = [1]
Output: 0
 

Constraints:

1 <= prices.length <= 105
0 <= prices[i] <= 105


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>

using namespace std;

int maxProfit(vector<int>& prices) {
	int n = prices.size();
	int last_buy = prices[0];
	int last_sell = prices[0];
	int max_profit = 0;
	for (int i = 1; i < n; ++i)
	{
		if (prices[i] < last_buy) {
			last_buy = prices[i];
			last_sell = last_buy;
		}else if (prices[i] > last_sell) {
			last_sell = prices[i];
			int profit = last_sell - last_buy;
			// 可开启第二次交易的条件：
			// 条件一：后面至少还有两个交易日，才能确保一次有效的交易，如果只有一个交易日，那么第二次交易利润为0
			// 条件二：下一个的股价低于当前股价，只有才有交易价值
			if (i < n-2 && prices[i+1] < prices[i]) {
				int sec_last_buy = prices[i+1];
				int sec_last_sell = sec_last_buy;
				int sec_profit = 0;
				for (int j = i+2; j < n; ++j)
				{
					if (prices[j] < sec_last_buy) {
						sec_last_buy = prices[j];
						sec_last_sell = sec_last_buy;
					}else if (prices[j] > sec_last_sell) {
						sec_last_sell = prices[j];
						sec_profit = max(sec_profit, sec_last_sell - sec_last_buy);
					}
				}
				profit += sec_profit;
			}
			max_profit = max(max_profit, profit);
		}
	}
	return max_profit;
}

int main(int argc, const char* argv[]) {
	// vector<int> prices = {3,3,5,0,0,3,1,4};
	// vector<int> prices = {1,2,3,4,5};
	// vector<int> prices = {3,2,6,5,0,3};
	vector<int> prices = {8,3,6,2,8,8,8,4,2,0,7,2,9,4,9};
	cout << "max profit: " << maxProfit(prices) << endl;
	return 0;
}