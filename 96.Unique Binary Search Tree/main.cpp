/*
Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.


Example 1:
Input: n = 3
Output: 5

Example 2:
Input: n = 1
Output: 1
 

Constraints:

1 <= n <= 19

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-binary-search-trees
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>

using namespace std;

// 题解：用dp[n]表示n个节点【可抽象为有序递增的节点列表】可构成二叉树的个数，n=0表示空二叉树，因此dp[0]=1, dp[1]=1
// 对于n>1的情况，当选择某一个节点i为根节点时，那么左边子树的节点数为i-1个，右边节点数为n-i个，此时可构成二叉树的个数为：dp[i-1]*dp[n-i]，
// dp[n] = ∑(i=1..n)dp[i-1]*dp[n-i]
int numTrees(int n) {
	if (n <= 1) return 1;
	// dp表示n个有序节点可构成BST树的个数
	int dp[n+1];
	// n=0，表示一颗空树
	dp[0] = 1;
	// n=1，只有一种情况
	dp[1] = 1;
	for (int i = 2; i <= n ; ++i) {
		dp[i] = 0;
		// i表示当前节点数，j表示选择的根节点
		// dp[i] = ∑(i=1..i)dp[j-1]*dp[i-j]
	 	for (int j = 1; j <= i; ++j) {
	 		// 累加选取不同根节点时的所构成的二叉树个数
	 		// dp[j-1]表示左边j-1个节点能构成的二叉树个数
	 		// dp[i-j]表示右边i-j个节点能构成的二叉树个数
	 		dp[i] += dp[j-1]*dp[i-j];
	 	}
	}
	return dp[n];
}

int main(int argc, const char* argv[]) {
	cout << "unique bianry search tree: " << numTrees(6) << endl;
	return 0;
}