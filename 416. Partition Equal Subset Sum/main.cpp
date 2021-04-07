/*
Given a non-empty array nums containing only positive integers, 
find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Example 1:
Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].

Example 2:
Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
 
Constraints:

1 <= nums.length <= 200
1 <= nums[i] <= 100
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool recursive(vector<int>& nums, int target, int i, vector<vector<int>>& memo_table) {
	if (target == 0) {
		return true;
	}else if (target < 0 || i < 0) {
		return false;
	}
	if (memo_table[target][i] >= 0) {
		return memo_table[target][i] == 0 ? false : true;
	}
	int new_target = target - nums[i];
	bool bRet =  recursive(nums, new_target, i - 1, memo_table) || recursive(nums, target, i - 1, memo_table);
	memo_table[target][i] = bRet ? 1 : 0;
	return bRet;
}

// Solution-01: Top-Down Approach
bool canPartition(vector<int>& nums) {
	bool bRet = false;
	int arr_size = nums.size();
	int arr_sum = 0;
	for (int i = 0; i < arr_size; ++i) {
		arr_sum += nums[i];
	}
	if (arr_sum % 2 != 0) return false;
	int target = arr_sum/2;
	vector<vector<int>> memo_table(target+1, vector<int>(arr_size, -1));
	cout << "arr_sum = " << arr_sum << endl;
	return recursive(nums, target, arr_size-1, memo_table);
}

// Solution-02: Bottom-Up Approach
bool canPartition_02(vector<int>& nums) {
	int arr_size = nums.size();
	int arr_sum = 0;
	for (int i = 0; i < arr_size; ++i) {
		arr_sum += nums[i];
	}
	cout << "arr_sum = " << arr_sum << endl;
	bool bRet = false;
	if (arr_sum % 2 != 0) return bRet;
	int target = arr_sum / 2;
	int dp_table[target+1];
	memset(dp_table, 0, sizeof(dp_table));

	for (int i = 0; i < arr_size; ++i) {
		int cur_num = nums[i];
		for (int j = target; j >= cur_num; j--) {
			// 判断j是否能通过当前元素以及在此之前的元素累加得到
			// dp_table将之前元素的运算结果保持，以实现不同组合的元素之间的运算叠加
			if (dp_table[j - cur_num] == 1 || j == cur_num) {
				dp_table[j] = 1;
			}
		}
	}

	return dp_table[target];
}

int main(int argc, const char** argv) {
	// vector<int> nums = {14,9,8,4,3,2};
	vector<int> nums = {1, 5, 11, 5};
	string ret = canPartition(nums) ? "true" : "false";
	cout<< "Can partitioned: " << ret << endl;
	return 0;
}