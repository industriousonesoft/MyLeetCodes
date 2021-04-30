/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and space is marked as 1 and 0 respectively in the grid.


Example 1:
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right


Example 2:
Input: obstacleGrid = [[0,1],[0,0]]
Output: 1
 

Constraints:

m == obstacleGrid.length
n == obstacleGrid[i].length
1 <= m, n <= 100
obstacleGrid[i][j] is 0 or 1.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-paths-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>

using namespace std;

int uniquePathsWithObstacles(vector<vector<int>>& inputs) {
    int row = inputs.size();
    if (row == 0) {
        return 0;
    }
    int col = inputs[0].size();
    int dp[row][col];
    memset(dp, 0, sizeof(dp));
    // 原点到自身的路径为1
    dp[0][0] = inputs[0][0] == 1 ? 0 : 1;
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            // 如果当前位置有障碍物说明不可通，因此到该位置的路径数量为0
            if (inputs[i][j] == 1) {
                dp[i][j] = 0;
            // 起始行的位置是否能到原点取决于其前面是否有障碍物
            }else if (i == 0) {
                if (j > 0) {
                    dp[i][j] = dp[i][j-1];
                }
            // 起始列的位置是否能到原点取决于其前面是否有障碍物
            }else if (j == 0) {
                if (i > 0) {
                    dp[i][j] = dp[i-1][j];
                }
            }else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
    }
    return dp[row-1][col-1];
}

int main(int argc, const char* argv[]) {
    vector<vector<int>> inputs = {{0,0,0}, {0,1,0}, {0,0,0}};
    // vector<vector<int>> inputs = {{0,1}, {0,0}};
    // vector<vector<int>> inputs = {{1,0}};
    cout << "Unique paths with obstacles: " << uniquePathsWithObstacles(inputs) << endl;
    return 0;
}