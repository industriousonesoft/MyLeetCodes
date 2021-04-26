/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*' where: 

'.' Matches any single character.​​​​
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).


Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
Example 4:

Input: s = "aab", p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
Example 5:

Input: s = "mississippi", p = "mis*is*p*."
Output: false
 

Constraints:

0 <= s.length <= 20
0 <= p.length <= 30
s contains only lowercase English letters.
p contains only lowercase English letters, '.', and '*'.
It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/regular-expression-matching
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// 理解： s = "ab", p = ".*"， *可以表示0个或多个在其前面的元素，因此".*"可以等价于".."与"ab"匹配
// 题解： s与p原字符串匹配的前提是各自的子串匹配，因此可原题拆分成子串匹配，用dp[i][j]表示长度为i的s子串与长度为j的p子串是否匹配

#include <iostream>

using namespace std;

// Solution-01，dp[i][j] = dp[i-1][j-1] && (a[i] == p[j])
bool isMatch(string& a, string& p) {
    int row = a.size();
    int col = p.size();
    if (row == 0 && col == 0) {
        return true;
    }
    // dp_table表示子串的匹配情况，下标分别代表a和p子串的长度，其中dp_table[0][0]表示二者都是空字符串
	bool dp_table[row+1][col+1];
    memset(dp_table, false, sizeof(dp_table));
    // dp_table[0][0]表示s和p子串均为空字符串，匹配成功
    dp_table[0][0] = true;

    // 因为*有效的前提是字符串长度至少是2，故下标从2开始
    for (int i = 2; i < col + 1; i++) {
        // 当a为空串时，只可能与p中的'*'匹配，'.'表示的是字符，故不能与空串匹配
        // 空串除了匹配空串，还可以匹配诸如：".*"或"a*b*c*"之类的字符串
        if (p[i-1] == '*') {
            dp_table[0][i] = dp_table[0][i-2];
        }
    }

    // dp_table下标表示的字符子串的长度，因此等于a,p字符串下标+1
    for (int i = 1; i < row + 1; i++) {
        for (int j = 1; j < col + 1; j++) {
            // 当前a与p的单个字符匹配成功，则对应的字符子串是否匹配取决于前面的字符是否匹配成功
            if (p[j-1] == '.' || a[i-1] == p[j-1]) {
                dp_table[i][j] = dp_table[i-1][j-1];
            // 当前字符为’*‘时，分两种情况：
            }else if (j > 1 && p[j-1] == '*') {
                // 情况一：’*‘的作用是消除前一个字符，因此当前子串的匹配结果与其在p[j-3]处的匹配结果一致
                // 理解难点：此处i的下标值未变，变化的是j的下标，是同一个a子串匹配不同的p子串，比如：ac可以同时匹配：ac和acd*
                dp_table[i][j] = dp_table[i][j-2];
                // 情况二：’*‘的作用拓展前一个字符，且扩展的字符与当前字符匹配
                if (p[j-2] == '.' || a[i-1] == p[j-2]) {
                    // 用’或‘操作符是为了将第一种情况考虑的结果进来，二选一只要有一种情况匹配即可
                    dp_table[i][j] = dp_table[i][j] | dp_table[i-1][j];
                }
            }
        }
    }
    
    return dp_table[row][col];
}

int main(int argc, const char* argv[]) {
    string a = "aa";
    string p = "a*";
    string result = isMatch(a, p) ? "macth" : "not match";
    cout << a << " is " << result <<" to '" << p << "'"<< endl;
    return 0;
}