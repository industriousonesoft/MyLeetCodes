#include <iostream>
#include <vector>

// 状态转移方程：LIS(i) = 1 + LIS(j), j < i, arr[j] < arr[i]
// 01-Recursive: 
int recurLIS(std::vector<int>& nums, int end_index, std::vector<int>& memo_table) {
	int max_length = 1;
	for (int i = end_index-1; i >= 0; i--) {
		if (nums[i] < nums[end_index]) {
			if (memo_table.size() > i && memo_table[i] > 0) {
				max_length = std::max(max_length, memo_table[i] + 1);
			}else {
				max_length = std::max(max_length, recurLIS(nums, i, memo_table) + 1);
			}
		}
	}
	memo_table[end_index] = max_length;
	return max_length;
}
 
int recurLengthOfLIS(std::vector<int>& nums) {
	int size = nums.size();
	if (size == 0) {
		return 0;
	}else if (size == 1) {
		return 1;
	}
	std::vector<int> memo_table(nums.size());
	int max_length = 0;
	for (int i = 0; i < nums.size(); ++i) {
		max_length = std::max(max_length, recurLIS(nums, i, memo_table));
	}
	return max_length;
}

// 02-Dynamic Programming Solution:
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

// The key logic we need to understand is: the end element of smaller list id smaller than the end element of larger lists.
// 03-Binary Search Soulution:
int bsSearchAndPosition(std::vector<int>& sorted_array, int end_index, int target_num) {
	int low_index = 0;
	int high_index = end_index;
	int mid_index = 0;
	int target_index = 0;
	while (low_index <= high_index) {
		mid_index = (low_index + high_index) / 2;
		int mid_num = sorted_array[mid_index];
		if (target_num > mid_num) {
			int next_index = mid_index + 1;
			// Extend the subsequence
			if (next_index > high_index) {
				target_index = next_index;
				break;
			// Replace the next one
			}else if (target_num < sorted_array[next_index]) {
			 	target_index = next_index;
			 	break;
			 // Continue to search
			}else {
			 	low_index = next_index;
			}
		}else if (target_num < mid_num) {
			int next_index = mid_index - 1;
			// Replace the first one 
			if (next_index < 0) {
				target_index = 0;
				break;
			// Replace the current one
			}else if (target_num > sorted_array[next_index]) {
				target_index = mid_index;
				break;
			// Continue to search
			}else {
				high_index = next_index;
			}
		// Found the same number
		}else {
			target_index = mid_index;
			break;
		}
	}
	sorted_array[target_index] = target_num;
	// Print the last element all the increasing subsequences
	for (int i = 0; i < sorted_array.size(); ++i)
	{
		if (sorted_array[i] != 0)
		{
			std::cout<< sorted_array[i] << " ";
		}
	}
	std::cout<< std::endl;
	// length = target_index + 1
	return target_index + 1;
}

int bsLengthOfLIS(std::vector<int>& nums) {
	int size = nums.size();
	if (size == 0) {
		return 0;
	}else if (size == 1) {
		return 1;
	}
	std::vector<int> end_elems_of_LISs(size, 0);
	end_elems_of_LISs[0] = nums[0];
	int max_length = 1;
	for (int i = 1; i < size; ++i) {
		max_length = std::max(bsSearchAndPosition(end_elems_of_LISs, max_length - 1, nums[i]), max_length);
	}
	return max_length;
}

// main
int main(int argc, const char * argv[]) {
	// std::vector<int> nums = {10,9,2,5,3,7,101,18};
	// std::vector<int> nums = {6,16,8,7,4,10,20,19,7,25,29,12};
	// std::vector<int> nums = {7,7,7,7,7,7,7};
	std::vector<int> nums = {3,5,6,2,5,4,19,5,6,7,12};

	// int ret = dpLengthOfLIS(nums);
	// std::cout << "dpLengthOfLIS: " << ret << std::endl;

	int ret = bsLengthOfLIS(nums);
	std::cout << "bsLengthOfLIS: " << ret << std::endl;

	return 0;
}