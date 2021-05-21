/*

Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

Example 1:
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:
Input: heights = [2,4]
Output: 4
 

Constraints:

1 <= heights.length <= 105
0 <= heights[i] <= 104


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/largest-rectangle-in-histogram
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>

using namespace std;

//解法一：为每一个高度确定左右边界，然后求面积。
// 时间复杂度： O(n^2)，空间复杂度：O(n), 但提交超时了
int largestRectangleArea(vector<int>& heights) {
	int cols = heights.size();
	if (cols == 0) return 0;
	int left[cols];
	int right[cols];
	// NOTE: memset内部实现只支持单字节赋值，如果cols是大于0的int类型（四个字节），则会去第一个字节赋值给目标数组，因此对于int数组，memset只能用于初始化0
	// 对于初始化为非0值，建议使用循环赋值的方式
	// memset(left, 0, sizeof(left));
	// memset(right, cols, sizeof(right));

	int area_max = 0;
	// 确定每个直方图的左边界
	for (int i = 0; i < cols; ++i) {
		left[i] = 0;
		for (int j = 0; j < i; ++j) {
			if (heights[i] > heights[j]) {
				left[i] = j+1;
			}
		}
	}

	for (int i = cols - 1; i >= 0; --i) {
		right[i] = cols;
		for (int j = cols - 1; j > i; --j) {
			if (heights[i] > heights[j]) {
				right[i] = j;
			}
		}
		if (right[i] > left[i] && heights[i] > 0) {
			area_max = max(area_max, (right[i] - left[i]) * heights[i]);
		}
	}

	return area_max;
}

// 解法二：先找到递增序列中的最大值，然后计算该值前的面积，然后继续寻找下一个递增序列的最大值，依次类推
int largestRectangleArea2(vector<int>& heights) {
	int cols = heights.size();
	if (cols == 0) return 0;
	int max_area = 0;
	for (int i = 0; i < cols; ++i)
	{
		// 寻找数组中的某个峰值
		if (i + 1 < cols && heights[i] < heights[i+1]) continue;

		// 计算该峰值之前的区域面积
		int minHeight = heights[i];
		max_area = max(max_area, heights[i]);
		for (int j = i - 1; j >= 0; --j)
		{
			// 因为j可能是在此峰值之前的某个峰值，因此min操作可确保当前j能够构成直方图
			minHeight = min(minHeight, heights[j]);
			max_area = max(max_area, (i - j + 1) * minHeight);
		}
	}
	return max_area;
}

int main(int argc, const char* argv[]) {
	// vector<int> heights = {2,1,5,6,2,3};
	// vector<int> heights = {2,4};
	// vector<int> heights = {6, 2, 5, 4, 5, 1, 6};
	vector<int> heights = {4,2,0,3,2,4,3,4};
	cout << "largetst rectangle area: " << largestRectangleArea2(heights) << endl;
	return 0;
}