/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

 

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input: s = "aa", p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input: s = "cb", p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:

Input: s = "adceb", p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:

Input: s = "acdcb", p = "a*c?b"
Output: false
 

Constraints:

0 <= s.length, p.length <= 2000
s contains only lowercase English letters.
p contains only lowercase English letters, '?' or '*'.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/wildcard-matching
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <string>

using namespace std;

/*
题解：s与p匹配的前提是各自的子串能匹配成功，因此把s和p拆分成不同子串进行匹配
用dp[i][j]标识长度为i的s子串与长度为j的p子串是否匹配，因此：dp[i][j] = dp[i-1][j-1] && (s[i] == p[j])
此外还需要对p子串中的?和*字符做特殊处理。
*/

bool isMatch(string s, string p) {
    int row = s.length();
    int col = p.length();
    bool dp[row+1][col+1];
    memset(dp, false, sizeof(dp));
    // dp[0][0]表示s和p均为空串，因此dp[0][0]=true
    dp[0][0] = true;
    // 因为p中可能连续存在多个’*‘, 所以s空串也可能匹配任意长度的p子串
    for (size_t i = 1; i < col + 1; i++) {
        if (p[i-1] == '*') {
            // 因为s此时是空串，所以'*'字符此时的匹配模式只匹配空串一种
            dp[0][i] = dp[0][i-1];
            cout << "0 => dp[0][" << i << "] = " << dp[0][i] << endl;
        }
    }

    for (size_t i = 1; i < row + 1; i++) {
        // 因为p中*的存在，s的任意长度的子串理论上可以匹配p任何长度的子串，因此j=1
        for (size_t j = 1; j < col + 1; j++) {
            // p[j-1]不为'*'时，只进行单个字符匹配
            if (p[j-1] == s[i-1] || p[j-1] == '?') {
                dp[i][j] = dp[i-1][j-1];
                cout << "1 => dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
             // 当前p的字符为’*‘，有3种匹配模式：
             // 1、’*‘只匹配一个字符
             // 2、’*‘匹配长度大于1的子串;
             // 3、’*‘匹配空串，
            }else if (p[j-1] == '*') {
                dp[i][j] = dp[i-1][j-1] /* 1 */ | dp[i-1][j] /* 2 */ | dp[i][j-1] /* 3 */;
                cout << "2 => dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
            }
        }
    }
    
    return dp[row][col];
}

int main(int argc, const char* argv[]) {
    // string s = "adceb", p = "*a*b";
    string s = "baaabab", p = "baaa?ab";
    string ret = isMatch(s, p) ? "match" : "not match";
    cout << "'" << s << "' is " << ret << " '" << p  << "'" << endl;
    return 0;
}
