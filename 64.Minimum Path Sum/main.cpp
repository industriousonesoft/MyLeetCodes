/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, 
which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example 1:
Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

Example 2:
Input: grid = [[1,2,3],[4,5,6]]
Output: 12
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 200
0 <= grid[i][j] <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-path-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>

using namespace std;

int minPathSum(vector<vector<int>>& grid) {
    int row = grid.size();
    if (row == 0) return 0;
    int col = grid[0].size();
    if (col == 0) return 0;
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            if (i == 0) {
                if (j > 0) {
                    grid[i][j] += grid[i][j-1];
                }
            }else if (j == 0) {
                if (i > 0) {
                    grid[i][j] += grid[i-1][j];
                }
            }else {
                grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
            }
        }
    }
    return grid[row-1][col-1];
}

int main(int argc, const char* argv[]) {
    // vector<vector<int>> grid = {{1,3,1}, {1,5,1}, {4,2,1}};
    vector<vector<int>> grid = {{1,2,3},{4,5,6}};
    int ret = minPathSum(grid);
    cout << "min path sum: " << ret << endl;
    return 0;
}