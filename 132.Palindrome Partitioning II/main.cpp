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
	// dp_cut[i]表示下标i之前的子串的最小切割次数，注：下标为i时，子串长度为i+1
	int dp_cut[n];
	memset(dp_cut, 0, sizeof(dp_cut));
	// dp_ps[i][j]表示下标i到j之间的子串是否是回文字符串
	bool dp_ps[n][n];
	memset(dp_ps, 0, sizeof(dp_ps));
	for (int r = 0; r < n; ++r) {
		// 长度为r+1的子串最大切割次数为r，即单个字符为一个回文子串
		dp_cut[r] = r;
		for (int l = 0; l <= r; ++l) {
			if (s[l] == s[r] && ( r - l < 3 || dp_ps[l+1][r-1] )) {
				dp_ps[l][r] = true;
				// 当l为0时表示不需要切割，因此一定是最小切割次数
				dp_cut[r] = l == 0 ? 0 : min(dp_cut[r], dp_cut[l-1] + 1);
			}
		}
	}
	return dp_cut[n-1];
}

int main(int argc, const char* argv[]) {
	string s = "aabbaaab";
	cout << "min cut: " << minCut(s) << endl;
	return 0;
}