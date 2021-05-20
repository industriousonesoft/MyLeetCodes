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

// 题解：这道题是在刷了85题之后顺带刷的同类型题目
// 数组进行三次扫描，第一次确定每一个高度所在的直方图的左边界，同理第二次是确定有边界，第三次则是计算每个直方图的面积，并比较出大最值。

#include <iostream>
#include <vector>

using namespace std;

int largestRectangleArea(vector<int>& heights) {
	int cols = heights.size();
	if (cols == 0) return 0;
	int left[cols];
	int right[cols];
	// NOTE: memset内部实现只支持单字节赋值，如果cols是大于0的int类型（四个字节），则会去第一个字节赋值给目标数组，因此对于int数组，memset只能用于初始化0
	// 对于初始化为非0值，建议使用循环赋值的方式
	// memset(left, 0, sizeof(left));
	// memset(right, cols, sizeof(right));

	for (int i = 0; i < cols; ++i) {
		left[i] = 0;
		right[i] = cols;
	}

	int area_max = 0;
	for (int i = 0; i < cols; ++i) {
		// 寻找左边界
		for (int j = 0; j < i; ++j) {
			if (heights[i] > heights[j]) {
				left[i] = j;
			}else {
				left[i] = left[j];
			}
		}

		// 寻找右边界
		for (int j = cols - 1; j > i; --j) {
			if (heights[i] > heights[j]) {
				right[i] = j;
			}else {
				right[i] = right[j];
			}
		}
		cout << endl;
		cout << "i: " << i << " - left: " << left[i] << " right: " << right[i] << " height: " << heights[i] << endl;
		if (right[i] > left[i] && heights[i] > 0) {
			area_max = max(area_max, (right[i] - left[i]) * heights[i]);
		}
	}

	return area_max;
}

int main(int argc, const char* argv[]) {
	vector<int> heights = {2,1,5,6,2,3};
	// vector<int> heights = {2,4};
	cout << "largetst rectangle area: " << largestRectangleArea(heights) << endl;
	return 0;
}