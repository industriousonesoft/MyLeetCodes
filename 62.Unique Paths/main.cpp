/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

Example 1:
Input: m = 3, n = 7
Output: 28

Example 2:
Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down

Example 3:
Input: m = 7, n = 3
Output: 28

Example 4:
Input: m = 3, n = 3
Output: 6
 
Constraints:

1 <= m, n <= 100
It's guaranteed that the answer will be less than or equal to 2 * 109.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-paths
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>

using namespace std;

int uniquePaths(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    int dp[m][n];
    memset(dp, 0, sizeof(dp));
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            // 到与起点在同一维度的点，只有一条路径可选
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            }else {
                // 与起点不再同一维度的点，存在向右和向下选择
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
    }
    return dp[m-1][n-1];
}

int main(int argc, const char* argv[]) {
    int m = 3, n = 0;
    cout << "m: " << m << " n: " << n << " res: " << uniquePaths(m, n) << endl; 
    return 0;
}