/*

Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

A palindrome string is a string that reads the same backward as forward.

 

Example 1:

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:
Input: s = "a"
Output: [["a"]]
 

Constraints:

1 <= s.length <= 16
s contains only lowercase English letters.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-partitioning
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

*/

#include <iostream>
#include <vector>

using namespace std;

// dp_pplists[n]表示下标n之前的字符串可拆分方式的组合
// dp[l][r]表示从下标范围l~r之间的子串是否是回文字符串
vector<vector<string>> partition(string s) {
	int n = s.length();
	vector<vector<vector<string>>> dp_pplists(n+1);
	dp_pplists[0].push_back({});
	bool dp[n][n];
	memset(dp, false, sizeof(dp));
	for (int r = 0; r < n; ++r)
	{
		for (int l = 0; l <= r; ++l)
		{
			if (s[l] == s[r] && ( (r - l <= 2) || dp[l+1][r-1] )) {
				dp[l][r] = true;
				auto sub_str = s.substr(l, r - l + 1);
				// 遍历l之前的子串的拆分方式
				for (auto list : dp_pplists[l]) {
					// 基于长度为j的子串拆分组合，加入新的回文子串，构建新的拆分队列
					list.push_back(sub_str);
					// 更新长度为r的子串的拆分组合
					dp_pplists[r+1].push_back(list);
				}
			}
		}
	}
	return dp_pplists[n];
}

int main(int argc, const char* argv[]) {
	vector<vector<string>> pplists = partition("aab");
	cout << pplists.size() << endl;
	cout << "[";
	for (int i = 1; i < pplists.size(); ++i)
	{
		auto pplist = pplists[i];
		cout << "[";
		for (int j = 0; j < pplist.size(); ++j)
		{
			cout << "\"" << pplist[i] << "\"";
		}
		cout << "],";
	}
	cout << "]" << endl;
	return 0;
}