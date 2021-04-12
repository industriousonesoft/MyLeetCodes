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

#include <iostream>

using namespace std;

bool isMatch(string& a, string& p) {
    int a_len = a.length();
    int p_len = p.length();
    int pos = 0;
    bool all_match = false;
    for (int i = 0; i < a_len; i++) {
       bool is_match = false; 
       for (int j = pos; j < p_len; j++) {
           if (p[j] == '.') {
               is_match = true;
               pos = j + 1;
               break;
           }else if (p[j] == '*') {
               if (p[j-1] == '.' || p[j-1] == a[i]) {
                   is_match = true;
                   if (p[j-1] != '.' && i + 1 < a_len && a[i] != a[i + 1]) {
                        pos = j + 1;
                   }
                   break;
               }else {
                   continue;
               }
           }else if (p[j] == a[i]) {
               is_match = true;
               pos = j + 1;
               break;
           }else if (p[j] != a[i] && j < p_len && p[j+1] == '.') {
               continue;
           }else {
               cout << i << ": " << a[i] << " vs " << j << ": "<< p[j] << endl;
               break;
           }
       }
       all_match = is_match;
       if (is_match == false) {
           cout << "break at " << i << " : "<< a[i] << endl;
           break;
       }
    }
    
    return all_match;
}

int main(int argc, const char* argv[]) {
    string a = "mississippi";
    string p = "mis*is*p*.";
    string result = isMatch(a, p) ? "macth" : "not match";
    cout << a << " is " << result <<" to '" << p << "'"<< endl;
    return 0;
}