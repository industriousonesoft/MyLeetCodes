/*
Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More formally, 
if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.

 

Example 1:

Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
Example 2:

Input: triangle = [[-10]]
Output: -10
 

Constraints:

1 <= triangle.length <= 200
triangle[0].length == 1
triangle[i].length == triangle[i - 1].length + 1
-104 <= triangle[i][j] <= 104

Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the triangle?

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/triangle
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>

using namespace std;

// Ver-01: 时间复杂度：O(n*(n+1)/2)， 空间复杂度：O(n^2)
int minimumTotal01(vector<vector<int>>& triangle) {
    int rows = triangle.size();
    if (rows == 0) return 0;
    if (rows == 1) return triangle[0][0];
    int dp[rows][rows];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = triangle[0][0];
    int sum = INT_MAX;
    for (int i = 1; i < rows; ++i) {
        auto list = triangle[i];
        int cols = list.size();
        dp[i][0] = dp[i-1][0] + list[0];
        dp[i][cols-1] = dp[i-1][cols-1-1] + list[cols-1];
        sum = min(dp[i][0], dp[i][cols-1]);
        for (int j = 1; j < cols - 1; ++j) {
            dp[i][j] = min(dp[i-1][j], dp[i-1][j-1]) + list[j];
            if (i == rows - 1) {
                sum = min(sum, dp[i][j]);
            }
        }
    }
    return sum;
}

// Ver-01: 时间复杂度：O(n*(n+1)/2)， 空间复杂度：O(n)
int minimumTotal(vector<vector<int>>& triangle) {
	int rows = triangle.size();
	if (rows == 0) return 0;
	if (rows == 1) return triangle[0][0];
	int dp[rows];
	memset(dp, 0, sizeof(dp));
	// dp[n]用于记录某一行中每一个元素的累加结果
	dp[0] = triangle[0][0];
	int sum = INT_MAX;
	for (int i = 1; i < rows; ++i) {
		auto list = triangle[i];
		int cols = list.size();
		dp[cols-1] = dp[cols-1-1] + list[cols-1];
		if (i == rows - 1) {
			sum = dp[cols-1];
		}
		// 因为下一行比上一行多一个元素，逆序遍历可确保在计算dp[j]时，dp[j-1]尚未被覆盖
		for (int j = cols - 1 - 1; j > 0; --j) {
			dp[j] = min(dp[j], dp[j-1]) + list[j];
			if (i == rows - 1) {
				sum = min(sum, dp[j]);
			}
		}
		dp[0] = dp[0] + list[0];
		if (i == rows - 1) {
			sum = min(sum, dp[0]);
		}
	}
	return sum;
}

int main(int argc, const char* argv[]) {
	vector<vector<int>> triangle = {{2},{3,4},{6,5,7},{4,1,8,3}};
	// vector<vector<int>> triangle = {{-10}};
	cout << "minimum total: " << minimumTotal(triangle) << endl;
	return 0;
}