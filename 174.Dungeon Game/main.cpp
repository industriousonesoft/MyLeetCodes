/*
The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon. 
The dungeon consists of m x n rooms laid out in a 2D grid. 
Our valiant knight was initially positioned in the top-left room and must fight his way through dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. 
If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons (represented by negative integers), 
so the knight loses health upon entering these rooms; other rooms are either empty (represented as 0) or 
contain magic orbs that increase the knight's health (represented by positive integers).

To reach the princess as quickly as possible, 
the knight decides to move only rightward or downward in each step.

Return the knight's minimum initial health so that he can rescue the princess.

Note that any room can contain threats or power-ups, even the first room the knight enters 
and the bottom-right room where the princess is imprisoned.

 
Example 1:
Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
Output: 7
Explanation: The initial health of the knight must be at least 7 if he follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.

Example 2:
Input: dungeon = [[0]]
Output: 1
 

Constraints:

m == dungeon.length
n == dungeon[i].length
1 <= m, n <= 200
-1000 <= dungeon[i][j] <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/dungeon-game
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>

using namespace std;

int calcMinHPSupplement(int healthPoint) {
	return healthPoint > 0 ? 0 : abs(healthPoint) + 1;
}

int calculateMinimumHP(vector<vector<int>>& dungeon) {
	int m = dungeon.size();
	if (m == 0) return 0;
	int n = dungeon[0].size();
	if (n == 0) return 0;
	int dp_left[m][n];
	memset(dp_left, 0, sizeof(dp_left));
	dp_left[0][0] = dungeon[0][0] > 0 ? dungeon[0][0] : 1;
	// dp[m][n]表示从（0,0）到达（m,n)时骑士需要初始化的最小血点值
	int dp_init[m][n];
	memset(dp_init, 0, sizeof(dp_init));
	dp_init[0][0] = calcMinHPSupplement(dungeon[0][0]);
	cout << endl;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == 0) {
				if (j > 0) {
					dp_left[i][j] = dp_left[i][j-1] + dungeon[i][j];
					dp_init[i][j] = dp_init[i][j-1];
				}
			}else if (j == 0) {
				if (i > 0) {
					dp_left[i][j] = dp_left[i-1][j] + dungeon[i][j];
					dp_init[i][j] = dp_init[i-1][j];
				}
			}else {
				if (dp_init[i-1][j] < dp_init[i][j-1]) {
					dp_left[i][j] = dp_left[i-1][j] + dungeon[i][j];
					dp_init[i][j] = dp_init[i-1][j];
				}else {
					dp_left[i][j] = dp_left[i][j-1] + dungeon[i][j];
					dp_init[i][j] = dp_init[i][j-1];
				}
			}
			if (dp_left[i][j] <= 0) {
				dp_init[i][j] += calcMinHPSupplement(dp_left[i][j]);
				dp_left[i][j] = 1;
			}
			cout << i << " - " << j << " - " << dp_init[i][j] << " - " << dp_left[i][j] << endl;
		}
	}
	return dp_init[m-1][n-1];
}

int main(int argc, const char* argv[]) {
	vector<vector<int>> dungeon = {{-2,-3,3}, {-5,-10,1}, {10,30,-5}};
	cout << "min health point: " << calculateMinimumHP(dungeon) << endl;
	return 0;
}