/*
Given an integer array arr, return the length of a maximum size turbulent subarray of arr.

A subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.

More formally, a subarray [arr[i], arr[i + 1], ..., arr[j]] of arr is said to be turbulent if and only if:

For i <= k < j:
arr[k] > arr[k + 1] when k is odd, and
arr[k] < arr[k + 1] when k is even.
Or, for i <= k < j:
arr[k] > arr[k + 1] when k is even, and
arr[k] < arr[k + 1] when k is odd.
 

Example 1:

Input: arr = [9,4,2,10,7,8,8,1,9]
Output: 5
Explanation: arr[1] > arr[2] < arr[3] > arr[4] < arr[5]
Example 2:

Input: arr = [4,8,12,16]
Output: 2
Example 3:

Input: arr = [100]
Output: 1
 

Constraints:

1 <= arr.length <= 4 * 104
0 <= arr[i] <= 109

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-turblulent-subarray
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
题解：

*/

#include <iostream>
#include <vector>
#include <string>

int maxTurbulenceSize(std::vector<int>& arr) {
    int arr_size = arr.size();
    if (arr_size == 0) {
    	return 0;
    }
    int max_size = 1;
    // 假设每个元素都有两条湍流，结尾的状态分别是上升和下降
    // 初始值设为1是因为湍流至少需要两个元素，因此对于单个元素的数组来说即是上升也是下降的，湍流长度都是1
    int preUp = 1;
    int preDown = 1;
    // preUp和preDown表示当前个元素结尾的湍流是上升还是下降的
    // 初始值为1是因为如果当前元素与前一个元素存在湍流关系，那么这个值会被重置，否则表示开始一个新的湍流，初始长度为1
    int curUp = 1;
    int curDown = 1;
    for (int i = 1; i < arr_size; i++) {
    	// 当前湍流是上升的，那么与前一个元素的下降湍流合并
    	if (arr[i] > arr[i-1]) {
    		curUp = preDown + 1;
    	}
    	// 当前湍流是下降的，那么与前一个元素的上升湍流合并
    	if (arr[i] < arr[i-1]) {
    		curDown = preUp + 1;
    	}
    	// 寻找目前为止的最长湍流
    	max_size = std::max(max_size, std::max(curUp, curDown));
    	// 记录以当前元素结尾的两条湍流长度，如果当前元素与上一个元素相等，意味着开始一个新的湍流
    	preUp = curUp;
    	preDown = curDown;
    	// 进入下一个元素的湍流数组计算，初始值为两条长度为1的湍流
    	curUp = 1;
    	curDown = 1;
    }
    return max_size;
}

int main(int argc, const char * argv[]) {
	std::vector<int> arr = {9,4,2,10,7,8,8,1,9};
	int max_size = maxTurbulenceSize(arr);
	std::cout << "max turbulent subarray size: " << max_size << std::endl;
	return 0;
}
