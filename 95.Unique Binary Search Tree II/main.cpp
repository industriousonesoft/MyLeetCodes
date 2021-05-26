/*
Given an integer n, return all the structurally unique BST's (binary search trees), 
which has exactly n nodes of unique values from 1 to n. Return the answer in any order.

 
Example 1:
Input: n = 3
Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]

Example 2:
Input: n = 1
Output: [[1]]

Constraints:

1 <= n <= 8

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-binary-search-trees-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

vector<TreeNode*> generateTrees(int n) {
	vector<TreeNode*> trees_0;
	if (n < 0) return trees_0;
	vector<TreeNode*> dp[n+1];
	trees_0.push_back(new TreeNode());
	dp[0] = trees_0;
	vector<TreeNode*> trees_1;
	trees_1.push_back(new TreeNode(1));
	dp[1] = trees_1;
	for (int i = 2; i <= n; ++i) {
		vector<TreeNode*> trees;
	 	for (int j = 1; j <= i; ++j) {
	 		vector<TreeNode*> left_trees = dp[j-1];
	 		vector<TreeNode*> right_trees = dp[i-j];
	 		for (int l = 0; l < left_trees.size(); l++) {
	 			for (int r = 0; r < right_trees.size(); r++) {
	 				trees.push_back(new TreeNode(j,left_trees[l],right_trees[r]));
	 			}
	 		}
	 	}
	 	dp[i] = trees;
	}
	return dp[n]; 
}

int main(int argc, const char* argv[]) {
	return 0;
}