/*
 * @Description: 
 * @Version: 
 * @Author: CaoWanPing
 * @Date: 2021-04-09 18:57:21
 * @LastEditTime: 2021-04-09 19:11:16
 */
/*
Given a string s, return the longest palindromic substring in s.

 

Example 1:

Input: s = "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"

Example 3:
Input: s = "a"
Output: "a"

Example 4:
Input: s = "ac"
Output: "a"
 

Constraints:

1 <= s.length <= 1000
s consist of only digits and English letters (lower-case and/or upper-case),


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-palindromic-substring
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
回文字符串的特点是字符串基于中点对称，且去掉两端的字符得到的子串也一定是回文字符串，此外单个字符也属于回文字符串。
求解最长回文字符串，将字符串看成一个字符数组，LP[i][j]表示下标i、j包含的回文字符串的长度，则状态转移方程为： 
LP[i][j] = LP[i+1][j-1] + 2, 0 <= i <= j, j < s.length
LP[i][i] = 1, 0 <= i < s.length
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// DP fomular: LP[i][j] = LP[i+1][j-1] + 2
// Solution: Bottom-Up Approach
string longestPalindrome2(string& str) {
	int size = str.size();
	int dp_table[size][size];
	memset(dp_table, 0, sizeof(dp_table));
	for (int i = 0; i < size; i++) {
		dp_table[i][i] = 1;
	}
	int max_l = 0;
	int max_r = 0;
	for (int len = 2; len <= size; len++) {
		for (int l = 0; l < size - len + 1; l++) {
			int r = l + len - 1;
			if (str[l] == str[r]) {
				// cout << "str[" << l << "]: " << str[l] << " - str[" << r << "]: " << str[r] << endl; 
				if (len == 2) {
					dp_table[l][r] = 2;
				// Make sure the substring is palindromic
				}else if (dp_table[l+1][r-1] > 0) {
					dp_table[l][r] = dp_table[l+1][r-1] + 2;
				}
				if (dp_table[l][r] > dp_table[max_l][max_r]) {
					max_l = l;
					max_r = r;
					// cout << "max_l: " << max_l << " - max_r: " << max_r << endl;
				}
			}
		}
	}
	return str.substr(max_l, max_r - max_l + 1);
}

string longestPalindrome3(string& str) {
	int size = str.size();
	int dp_table[size][size];
	memset(dp_table, 0, sizeof(dp_table));
	int max_l = 0;
	int max_r = 0;
	for (int len = 1; len <= size; len++) {
		for (int l = 0; l < size - len + 1; l++) {
			int r = l + len - 1;
			if (str[l] == str[r]) {
				// cout << "str[" << l << "]: " << str[l] << " - str[" << r << "]: " << str[r] << endl; 
				if (len <= 3) {
					dp_table[l][r] = len;
				// Make sure the substring is palindromic
				}else if (dp_table[l+1][r-1] > 0) {
					dp_table[l][r] = dp_table[l+1][r-1] + 2;
				}
				if (dp_table[l][r] > dp_table[max_l][max_r]) {
					max_l = l;
					max_r = r;
					// cout << "max_l: " << max_l << " - max_r: " << max_r << endl;
				}
			}
		}
	}
	return str.substr(max_l, max_r - max_l + 1);
}

// A more efficient and clear approach
string longestPalindrome(string& str) {
	int n = str.length();
	int dp[n][n];
	memset(dp, 0, sizeof(dp));
	int max_l = 0;
	int max_r = 0;
	for (int r = 0; r < n; ++r)
	{
		for (int l = 0; l <= r; ++l)
		{
			if (str[l] == str[r]) {
				int len = r - l + 1;
				 if (len <= 3) {
				 	dp[l][r] = len;
				 }else if (dp[l+1][r-1] > 0) {
				 	dp[l][r] = dp[l+1][r-1] + 2;
				 }
				 if (dp[l][r] > dp[max_l][max_r]) {
				 	max_l = l;
				 	max_r = r;
				 }
			}
		}
	}
	return str.substr(max_l, max_r - max_l + 1);
}

int main(int argc, const char * argv[]) {
	string str = "aacabdkacaa";
	string result = longestPalindrome(str);
	cout << "longest palindrome: " << result << endl;
	return 0;
}