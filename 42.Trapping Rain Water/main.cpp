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

// Approach-01: 时间复杂度O(n^2)，空间复杂度O(1)
int trap_01(vector<int>& nums) {
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

// Approach-02: 时间复杂度O(n)， 空间复杂度O(n*2)
// 题解：每一个数字看成一个宽度为1的蓄水单元，且相互孤立，而某个单元是否可蓄水取决于其左右两边是否均有比其更高的单元，如果表示可蓄水，且蓄水高度取决于两边较低的单元
int trap(vector<int>& nums) {
    int count = nums.size();
    if (nums.size() == 0) {
        return 0;
    }
    int right[count];
    int left[count];
    // NOTE: 此处应该用sizeof来计算数组的长度，把数组类型考虑在其中，而非直接使用n
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    // 统计第i个单元左边最大的高度值，不包括i单元本身
    // 由于i=0时无左边单元，因此下标从0开始
    for (int i = 1; i < count; i++) {
        left[i] = max(left[i - 1], nums[i - 1]);
    }
    // 统计第i个单元右侧最大的高度值，不包括i单元本身
    // 由于第n-1个单元无右边单元，因此下标从n-2开始
    for (int i = count - 2; i >= 0; i--) {
        right[i] = max(right[i + 1], nums[i + 1]);
    }
    int sum = 0;
    int top = 0;
    int bottom = 0;
    // 计算每一个单元的蓄水量
    // 因为第一个和最后一个单元都是边界单元，本身不能蓄水
    for (int i = 1; i < count - 1; i++) {
        // 蓄水高度取决于单元两侧峰值中较低的一个高度值
        top = min(left[i], right[i]);
        bottom = nums[i];
        // 因为width = 1，因此蓄水面积之间等于高度差
        // 用因为如果两侧峰值均小于当前元素的高度，计算结果为负值，表示当前单元无蓄水能力，用0表示
        sum += max(0, top - bottom);
    }
    return sum;
}

int main(int argc, const char* argv[]) {
    // vector<int> nums = {0,1,0,2,1,0,1,3,2,1,2,1};
    // vector<int> nums = {4,2,0,3,2,5};
    // vector<int> nums = {5,4,1,2};
    vector<int> nums = {4,2,3};
    cout << " traped water: " << trap(nums) << endl;
    return 0;
}