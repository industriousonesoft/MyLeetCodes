/*
Given two strings s and t, return the number of distinct subsequences of s which equals t.
A string's subsequence is a new string formed from the original string 
by deleting some (can be none) of the characters without disturbing the remaining characters' relative positions. 
(i.e., "ACE" is a subsequence of "ABCDE" while "AEC" is not).

It is guaranteed the answer fits on a 32-bit signed integer.

Example 1:

Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from S.
rabbbit
rabbbit
rabbbit


Example 2:
Input: s = "babgbag", t = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from S.
babgbag
babgbag
babgbag
babgbag
babgbag
 

Constraints:

1 <= s.length, t.length <= 1000
s and t consist of English letters.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/distinct-subsequences
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>

using namespace std;

int numDistinct(string s, string t) {
	int s_size = s.size();
	int t_size = t.size();
	// dp[m][n]表示长度为m的s子串中包含长度为n的t子串的次数
	unsigned int dp[s_size+1][t_size+1];
	dp[0][0] = 1;
	// t为空串时，可以匹配一次任意长度的s子串
	for (int i = 1; i <= s_size; ++i) {
		dp[i][0] = 1;
	}
	// s为空串时，任意非0长度的t子串都不可能匹配成功
	for (int i = 1; i <= t_size; ++i) {
		dp[0][i] = 0;
	}
	for (int i = 1; i <= s_size; ++i) {
		for (int j = 1; j <= t_size; ++j) {
			// s和t当前子串的最后一次的字符不匹配，则当前t子串与长度为i的s子串匹配次数等于与长度为i-1的s子串的匹配次数
			if (s[i-1] != t[j-1]) {
				dp[i][j] = dp[i-1][j];
			}else {
				// s和t当前子串的最后一次的字符匹配时，当前子串有两种匹配选择：
				// 1. 忽略当前字符匹配，让长度为i-1的s子串匹配长度为j的t子串
				// 2. 记录当前字符匹配，长度为i的s子串与长度为j的t子串匹配次数等于长度为i-1的s子串与长度为j-1的t子串匹配次数
				dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
			}
		}
	}
	return dp[s_size][t_size];
}

int main(int argc, const char* argv[]) {
	string s = "babgbag";
	string t = "bag";
	cout << " num distinct: " << numDistinct(s, t) << endl;
	return 0;
}