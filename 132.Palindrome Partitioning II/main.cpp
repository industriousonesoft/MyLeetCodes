/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

 
Example 1:
Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

Example 2:
Input: s = "a"
Output: 0

Example 3:
Input: s = "ab"
Output: 1
 

Constraints:

1 <= s.length <= 2000
s consists of lower-case English letters only.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-partitioning-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>

using namespace std;

int minCut(string s) {
	int n = s.size();
	// dp_count[i]用于记录长度为i的子串可拆分的组合的长度
	vector<vector<int>> dp_count(n+1);
	dp_count[0].push_back(0);
	// dp_ps[i][j]表示下标i到j之间的子串是否是回文字符串
	bool dp_ps[n][n];
	memset(dp_ps, 0, sizeof(dp_ps));
	for (int r = 0; r < n; ++r)
	{
		for (int l = 0; l <= r; ++l)
		{
			if (s[l] == s[r] && ( r - l < 3 || dp_ps[l+1][r-1] )) {
				dp_ps[l][r] = true;
				for (auto count : dp_count[l])
				{
					count += 1;
					dp_count[r+1].push_back(count);
				}
			}
		}
	}
	int min_count = dp_count[n][0];
	for (int i = 1; i < dp_count[n].size(); ++i)
	{
		min_count = min(min_count, dp_count[n][i]);
	}
	return min_count - 1;
}

int main(int argc, const char* argv[]) {
	string s = "aabaaab";
	cout << "min cut: " << minCut(s) << endl;
	return 0;
}