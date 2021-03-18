#include <iostream>
#include <vector>

int maxSubarray(std::vector<int>& nums) {
	int max = 0;
	for (int i = 0; i < nums.size(); ++i)
	{	int sum_max = nums[i];
		int sum = nums[i];
		for (int j = i + 1; j < nums.size(); ++j)
		{
			sum += nums[j];
			sum_max = std::max(sum_max, sum);
		}
		max = std::max(max, sum_max);
	}
	return max;
}

int maxSubarray2(std::vector<int>& nums) {
	// std::vector<int> dp_table = std::vector<int>(nums);
	// dp_table[0] = nums[0];
	int max = nums[0];
	int front_sub_max = nums[0];
	for (int i = 1; i < nums.size(); ++i)
	{
		// dp[i] = max(num[i], num[i] + dp[i-1])
		// 计算包含i的最大子集和: 
        // num[i]: 表示从当前元素开始一个新子集
        // nums[i] + dp_table[i-1]: 表示延续i-1的最大和子集
		// dp_table[i] = std::max(nums[i], nums[i] + dp_table[i-1]);
		// max = std::max(max, dp_table[i]);
		front_sub_max = std::max(nums[i], nums[i] + front_sub_max);
		max = std::max(front_sub_max, max);
	}
	return max;
}

int main(int argc, const char * argv[]) {

// Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
// Output: 6
// Explanation: [4,-1,2,1] has the largest sum = 6.

	// std::vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
	// std::vector<int> nums = {1};
	std::vector<int> nums = {5,4,-1,7,8};

	std::cout << "maxSubarray: " << maxSubarray2(nums) << std::endl; 

	return 0;
}