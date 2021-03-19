#include <iostream>
#include <vector>

// 状态转移方程：LIS(i) = 1 + LIS(j), j < i, arr[j] < arr[i]
// Recursive Solution: 
int recurLIS(std::vector<int>& nums, int end_index, std::vector<int>& dp_table) {
	int max_length = 1;
	for (int i = end_index-1; i >= 0; i--) {
		if (nums[i] < nums[end_index]) {
			if (dp_table.size() > i && dp_table[i] > 0) {
				max_length = std::max(max_length, dp_table[i] + 1);
			}else {
				max_length = std::max(max_length, recurLIS(nums, i, dp_table) + 1);
			}
		}
	}
	dp_table[end_index] = max_length;
	return max_length;
}
 
int recurLengthOfLIS(std::vector<int>& nums) {
	int size = nums.size();
	if (size == 0) {
		return 0;
	}else if (size == 1) {
		return 1;
	}
	std::vector<int> dp_table(nums.size());
	int max_length = 0;
	for (int i = 0; i < nums.size(); ++i) {
		max_length = std::max(max_length, recurLIS(nums, i, dp_table));
	}
	return max_length;
}

// Dynamic Programming Solution:
int dpLengthOfLIS(std::vector<int>& nums) {
	int size = nums.size();
	if (size == 0) {
		return 0;
	}else if (size == 1) {
		return 1;
	}
	std::vector<int> dp_table(size, 1);
	int max_length = 0;
	for (int i = 1; i < size; ++i) {
		for (int j = 0; j < i; ++j) {
			if (nums[i] > nums[j]) {
				dp_table[i] = std::max(dp_table[j] +1, dp_table[i]);
			}
		}
		max_length = std::max(max_length, dp_table[i]);
	} 
	return max_length;
}

// Dinary Search Soulution:
int BS_lengthOfLIS(std::vector<int>& nums) {
	return 0;
}

int main(int argc, const char * argv[]) {
	std::vector<int> nums = {10,9,2,5,3,7,101,18};
	// std::vector<int> nums = {6,16,8,7,4,10,20,19,7,25,29,12};
	// std::vector<int> nums = {7,7,7,7,7,7,7};
	int ret = dpLengthOfLIS(nums);
	std::cout << "lengthOfLIS: " << ret << std::endl;
	return 0;
}