/*
There is only one character 'A' on the screen of a notepad. You can perform two operations on this notepad for each step:

Copy All: You can copy all the characters present on the screen (a partial copy is not allowed).
Paste: You can paste the characters which are copied last time.

Given an integer n, return the minimum number of operations to get the character 'A' exactly n times on the screen.


Example 1:
Input: n = 3
Output: 3
Explanation: Intitally, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.

Example 2:
Input: n = 1
Output: 0
 

Constraints:

1 <= n <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/2-keys-keyboard
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include<iostream>

using namespace std;

// 题解：把原问题抽象为将字符A使用复制黏贴的方式变成n个A字符
// 由于只能全选复制不能部分选中复制，用dp[n]表示得到长度为n的字符串需要的最少操作步骤，因此有三种基本情况：
// n = 1，不需要操作，dp[0] = 0
// n是非素数, 因式分解n=ixj，将长度为i的字符串设置B，问题变成使用最少次数可以将B字符串变成j个B字符串，将求dp[n]转变成求dp[j]的问题，且dp[n] = dp[i] /* 先获得长度为i的子串需要的最少步骤 */ + dp[j] /* 然后再基于长度为i的B字符串，获得j个B子串的最少步骤 */
// n是素数，dp[n] = dp[0] + n
// 至此原问题转变成了判断数字n是否为素数的问题
int minSteps(int n) {
	if (n <= 1) return 0;
	int dp[n+1];
	memset(dp, 0, sizeof(dp));
	dp[2] = 2;
	for (int i = 2; i < n + 1; ++i) {
		dp[i] = i;
		for (int j = 2; j < i; ++j) {

		}
	}
	return 0;
}

int main(int argc, const char* argv[]) {
	cout << "Min steps: " << minSteps(9) << endl;
	return 0;
}
