/*
Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.

An interleaving of two strings s and t is a configuration where they are divided into non-empty substrings such that:

s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
Note: a + b is the concatenation of strings a and b.

 
Example 1:
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true

Example 2:
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false

Example 3:
Input: s1 = "", s2 = "", s3 = ""
Output: true
 

Constraints:

0 <= s1.length, s2.length <= 100
0 <= s3.length <= 200
s1, s2, and s3 consist of lowercase English letters.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/interleaving-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>

using namespace std;

// 题解一：错误！！想法是使用两个下标分别标识s1和s2当前匹配的位置，这种思路的弊端在于不能覆盖所有拼凑的情况，
// 因此某个位置的字符来源是随机的
/*
bool isInterleave(string s1, string s2, string s3) {
        int size1 = s1.size();
        int size2 = s2.size();
        int size3 = s3.size();
        if (size1 + size2 != size3) return false;
        if (size1 == 0 && size2 == 0) return true;
        if (size1 == 0) return s2 == s3;
        if (size2 == 0) return s1 == s3;
        int index1 = 0, index2 = 0;
        // 该标识用于记录上一次匹配成功的字符串，下一次匹配时延续上一次匹配的位置继续匹配
        // 最极端的情况是每一个位置的字符交替来自不同的字符串
        int lastMatchedS1 = true;
        bool bRet = true;
        for (int i = 0; i < size3; ++i) {
            if (lastMatchedS1) {
                if (s3[i] == s1[index1]) {
                    index1 += 1;
                    lastMatchedS1 = true;
                }else if (s3[i] == s2[index2]) {
                    index2 += 1;
                    lastMatchedS1 = false;
                }else { 
                    bRet = false;
                    break;
                }
            }else {
                if (s3[i] == s2[index2]) {
                    index2 += 1;
                    lastMatchedS1 = false;
                }else if (s3[i] == s1[index1]) {
                    index1 += 1;
                    lastMatchedS1 = true;
                }else { 
                    bRet = false;
                    break;
                }
            }

        }
        return bRet;
    }
*/

// 题解二：使用二维数组dp[i][j]表示长度为1的s1子串和长度为j的s2子串能否拼凑成长度为i+j的s3子串
// 这样可以记录s1和s2子串每一种组合情况的匹配情况
// 最终字符串的匹配情况取决于子串的匹配情况
bool isInterleave(string s1, string s2, string s3) {
	int size1 = s1.size();
	int size2 = s2.size();
	int size3 = s3.size();
	if (size1 + size2 != size3) return false;
	if (size1 == 0 && size2 == 0) return true;
	if (size1 == 0) return s2 == s3;
	if (size2 == 0) return s1 == s3;
	// dp[i][j]表示长度为1的s1子串和长度为j的s2子串能否拼凑成长度为i+j的s3子串
	bool dp[size1+1][size2+1];
	memset(dp, false, sizeof(dp));
	dp[0][0] = true;
	for (int i = 0; i <= size1; ++i) {
		for (int j = 0; j <= size2; ++j) {
			if (i == 0 && j > 0) {
				dp[i][j] = dp[i][j-1] && s2[j-1] == s3[i+j-1];
			}else if (j == 0 && i > 0) {
				dp[i][j] = dp[i-1][j] && s1[i-1] == s3[i+j-1];
			}else if (i > 0 && j > 0){
				dp[i][j] = (dp[i][j-1] && s2[j-1] == s3[i+j-1]) || (dp[i-1][j] && s1[i-1] == s3[i+j-1]);
			}
		}
	}
	return dp[size1][size2];
}

int main(int argc, const char* argv[]) {
	// string s1 = "aabcc";
	// string s2 = "dbbca";
	// string s3 = "aadbbbaccc";
	string s1 = "aa";
	string s2 = "ab";
	string s3 = "aaba";
	string ret = isInterleave(s1, s2, s3) ? "true" : "false";
	cout << s3 << " is interleaving string: " << ret << endl;
	return 0;
}