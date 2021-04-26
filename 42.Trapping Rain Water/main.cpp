/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. 
In this case, 6 units of rain water (blue section) are being trapped.

Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9
 
Constraints:

n == height.length
0 <= n <= 3 * 104
0 <= height[i] <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/trapping-rain-water
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>

using namespace std;

int trap(vector<int>& nums) {
    size_t count = nums.size();
    if (nums.size() == 0) {
        return 0;
    }
    int sum = 0;
    int width = 0;
    int height = 0;
    int bottom = 0;
    for (size_t i = 0; i < count; i++) {
        // 高度下于0表示没有蓄水的可能
        if (nums[i] <= 0) continue;
        bottom = 0;
        height = nums[i];
        for (size_t j = i + 1; j < count; j++) {
            // 高度为0不可构成蓄水池
            if (nums[j] <= 0) continue;
            // 当前起始值<=当前结束值时，表示可构成蓄水池，且当前蓄水池不可再拓展
            if (nums[i] <= nums[j])  {
                // 计算蓄水池宽度
                width = j - i - 1;
                sum += width * height;
                cout << "1 - i: " << i << "- j: " << j << " => w: " << width << " h: " << height << endl;
                // 寻找下一个蓄水池
                break;
            }else {
                int newHeight = nums[i] - nums[j];
                // 如果当前值可以构成蓄水池，那么比当前值更小的值也肯定可以构成蓄水池，减去子蓄水池的高度，避免重复计算
                // 当前起始值>当前结束值时，且出现了更小的高度值，表示二者之间没有阻隔，可构成蓄水池
                if (newHeight < height) {
                    width = j - i - 1;
                    height = newHeight;
                    // 蓄水池高度取决于较低的一端
                    sum += width * (nums[j] - bottom);
                    cout << "2 - i: " << i << "- j: " << j << " => w: " << width << " h: " << height <<" b: " << bottom << endl;
                }
                // 更新当前蓄水池的底部高度
                bottom = max(bottom, nums[j]);
            }
        }
        
    }
    
    return sum;
}

int main(int argc, const char* argv[]) {
    // vector<int> nums = {0,1,0,2,1,0,1,3,2,1,2,1};
    vector<int> nums = {4,2,0,3,2,5};
    // vector<int> nums = {5,4,1,2};
    cout << " traped water: " << trap(nums) << endl;
    return 0;
}