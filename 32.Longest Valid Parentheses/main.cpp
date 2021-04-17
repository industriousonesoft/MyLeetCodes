/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

 

Example 1:

Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".
Example 2:

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".
Example 3:

Input: s = ""
Output: 0
 

Constraints:

0 <= s.length <= 3 * 104
s[i] is '(', or ')'.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-valid-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// 题解：所谓有效是指括号是成对且连续的

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Solution-01: 时间复杂度O(n^2) 空间复杂度O(n)
int longestValidParentheses_01(string str) {
    int max_len = 0;
    // 用vector代替stack，原因是vector可通过clear进行重用
    // 用栈结构来模拟括号匹配操作
    vector<char> stack;
    for (int i = 0; i < str.length(); i++) {
        int sub_len = 0;
        int matched_count = 0;
        for (int j = i; j < str.length(); j++) {
            if (str[j] == '(') {
                stack.push_back(str[j]);
            }else if (str[j] == ')') {
                if (!stack.empty()) {
                    // 由于已知只有小括号匹配，省略了比较操作，出栈即可。如果有多种括号类型，则需要一一匹配
                    stack.pop_back();
                    matched_count += 1;
                    // 栈清空才说明前面加入的左括号全部匹配
                    if (stack.empty()) {
                        sub_len += matched_count * 2;
                        matched_count = 0;
                    }
                // 一旦括号匹配失败说明不再是有效的括号（连续性），退出循环
                }else {
                    break;
                }
            }
        }
        stack.clear();
        max_len = max(max_len, sub_len);
    }
    return max_len;
}

// Solution-02: 时间复杂度：O(n)，空间复杂度O(n)
int longestValidParentheses_02(string str) {
    int max_len = 0;
    int last_end_index = -1;
    // 用栈结构来模拟括号匹配操作
    vector<int> stack;
    for (int i = 0; i < str.length();i++) {
        if (str[i] == '(') {
            stack.push_back(i);
        }else {
            // 无左括号可匹配
            if (stack.empty()) {
                last_end_index = i;
            }else {
                stack.pop_back();

                // 栈中的所有左括号匹配完成
                if (stack.empty()) {
                    max_len = max(max_len, i-last_end_index);
                // 计算已匹配的长度
                }else {
                    max_len = max(max_len, i-stack.back());
                }
            }
        }
    }
    return max_len;
}

// Solution-03: Dynamic Programing
int longestValidParentheses(string str) {
    int size = str.size();
    if (size <= 0) return 0;
    int max_len = 0;
    // dp_table[i]表示下标i对应的有效括号字符串长度
    int dp_table[size];
    memset(dp_table, 0, sizeof(dp_table));

    for (int i = 1; i < size; i++) {
        if (str[i] == ')') {
            int left_i = i - dp_table[i-1] - 1;
            if (left_i >= 0 && str[left_i] == '(') {
                // dp_table[i-1] + 2表示嵌套的括号字符串，dp_table[left_i-1]表示前面连续的有效字符串
                dp_table[i] = dp_table[i-1] + 2 + (left_i - 1 >= 0 ? dp_table[left_i-1] : 0);
            }
        }
        max_len = max(max_len, dp_table[i]);
    }

    return max_len;
}

int main(int argc, const char* argv[]) {
    string s = "()(())";
    // string s = ")()())";
    cout << "The longest valid parentheses substring len: " << longestValidParentheses(s) << endl;
    return 0;
}

