/*
 * @Description: 
 * @Version: 
 * @Author: CaoWanPing
 * @Date: 2021-03-16 18:52:12
 * @LastEditTime: 2021-04-09 18:56:38
 */
/*
The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,

F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.
Given n, calculate F(n).

 

Example 1:

Input: n = 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.
Example 2:

Input: n = 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.
Example 3:

Input: n = 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
 

Constraints:

0 <= n <= 30

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/fibonacci-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
题解：
Fibonacci Number是我刷动态规划的第一道题，最开始想到的解题方法是递归，效率自然不高。后面翻阅”labuladong的算法小抄“一书，了解到动态规划的解题思想。
动态规划一般是用于求解最值问题，且通常包含三要素：重叠子问题，最优子结构、状态转移方程。
- 重叠子问题：由于动态规划本质是穷举，因此使用递归的话则不可避免的会出现重复运算，可采样”备忘录“的方式记录计算结果来避免重叠运算；
- 最优子结构：由于动态规划一般用于求解最值，那么将原问题拆分成相互独立的子问题，通过求子问题的最值来得到原问题的最值；
- 状态转移方程：我的理解是用于表达将原问题拆分成子问题的方程，包括边界值得限定等；
其中，找出状态转移方程是动态规划中最难的步骤。
求解Fibonacci Number虽然不是求解最值，但也可通过动态规划求解，而且它的状态转移方程就是Fibonacci Number的推导公式本身
*/

#include <iostream>
#include <vector>

using namespace std;

// Solution-01: Top-Down Approach
// 自顶向下：递归+备忘录
// Time Complexity: 不使用备忘录为O(2^n)，因为每次递归都变成两次子递归，运算呈指数增加；使用备忘录为O(n)，因为屏蔽重叠运算，每个数只运算一次，运算是线性增加
// Space Complexity: 不使用备忘录为O(1)；使用备忘录为：O(n)
int recursive(int n, vector<int> memo_table) {
    if (n <= 0) {
        return 0;
    }else if (n == 1) {
        return 1;
    }
    if (memo_table[n] > 0) return memo_table[n];
    return recursive(n-1, memo_table) + recursive(n-2, memo_table);
}

int fib(int n) {
    vector<int> memo_table(n, 0);
    return recursive(n, memo_table);
}

// Solution-02: Bottom-Up Approach
// 自底向上：根据状态转移方程，由已知推导出未知，且后一个数只取决于其前面的两个数，因此只需要保存当前数的前两个数即可，初始值分别是f(0)=0和f(1)=1
int fib_2(int n) {
    if (n < 0) {
        throw "Invalid Input.";
    }else if (n == 0) {
        return 0;
    }else if (n == 1) {
        return 1;
    }
    int sum = 0;
    int pre = 0;
    int cur = 1;
    for (int i = 2; i <= n; i++) {
        sum = pre + cur;
        pre = cur;
        cur = sum;
    }
    return sum;
}

int main(int argc, const char * argv[]) {
	int n = 2;
    std::cout << "fib(" << n << ") = " << fib(n) << std::endl;
}