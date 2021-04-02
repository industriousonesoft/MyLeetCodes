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

bool canPartition(vector<int>& nums) {
	int arr_size = nums.size();
	int dp_table[arr_size][arr_size];
	memset(dp_table, 0, sizeof(dp_table));
	int arr_sum = 0;
	for (int i = 0; i < arr_size; ++i) {
		arr_sum += nums[i];
	}
	cout << "arr_sum = " << arr_sum << endl;
	if (arr_sum % 2 != 0) return false;
	bool bRet = false;
	
	return bRet;
}

int main(int argc, const char** argv) {
	vector<int> nums = {14,9,8,4,3,2};
	string ret = canPartition(nums) ? "true" : "false";
	cout<< "Can partitioned: " << ret << endl;
	return 0;
}