/*
Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.


Example 1:
Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6

Example 2:
Input: matrix = []
Output: 0

Example 3:
Input: matrix = [["0"]]
Output: 0

Example 4:
Input: matrix = [["1"]]
Output: 1

Example 5:
Input: matrix = [["0","0"]]
Output: 0
 

Constraints:

rows == matrix.length
cols == matrix[i].length
0 <= row, cols <= 200
matrix[i][j] is '0' or '1'.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximal-rectangle
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include<iostream>
#include<vector>

using namespace std;

// 题解一：使用一个四维数组dp[i][j][end_i][end_j]表示从点(i,j)到点（end_i, end_j）能否构成一个矩形，
// 所以dp[i][j][end_i][end_j] = dp[i][j][end_i-1][end_j] && dp[i][j][end_i][end_j-1]
// 时间复杂度： O(m^2xn^2) 空间复杂度：O(mxmxnxn)
int maximalRectangle(vector<vector<char>>& matrix) {
	if (matrix.size() == 0) return 0;
	int rows = matrix.size();
	int cols = matrix[0].size();
	bool dp[rows][cols][rows][cols];
	memset(dp, false, sizeof(dp));
	int max_sum = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			// 矩形的起点值不能为0
			if (matrix[i][j] == '0') continue;
			for (int end_i = i; end_i < rows; ++end_i) {
				for (int end_j = j; end_j < cols; ++end_j) {
					// 如果矩形当前终点值为0，说明后续值不再可能构成局限，中止当前循环
					if (matrix[end_i][end_j] == '0') break;
					if (end_i > i && !dp[i][j][end_i-1][end_j]) break;
					if (end_j > j && !dp[i][j][end_i][end_j-1]) break;
					dp[i][j][end_i][end_j] = true;
					int width = end_i - i + 1;
					int height = end_j - j + 1;
					int sum = width * height;
					max_sum = max(max_sum, sum);
				}
			}
		}
	}
	return max_sum;
}

// 题解二：将二维数据抽象成直方图，将行看成是直方图的横坐标轴，列为直方图的纵坐标轴，原问题变成求直方图中面积最大的矩形

int main(int argc, const char* argv[]) {
	vector<vector<char>> matrix = {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
	cout << "max sum: " << maximalRectangle(matrix) << endl;
	return 0;
}