/*
You are given an array of binary strings strs and two integers m and n.

Return the size of the largest subset of strs such that there are at most m 0's and n 1's in the subset.

A set x is a subset of a set y if all elements of x are also elements of y.

Example 1:

Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
Output: 4
Explanation: The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"}, so the answer is 4.
Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
{"111001"} is an invalid subset because it contains 4 1's, greater than the maximum of 3.
Example 2:

Input: strs = ["10","0","1"], m = 1, n = 1
Output: 2
Explanation: The largest subset is {"0", "1"}, so the answer is 2.
 

Constraints:

1 <= strs.length <= 600
1 <= strs[i].length <= 100
strs[i] consists only of digits '0' and '1'.
1 <= m, n <= 100
*/

/*
这道题与“找零钱”问题的逻辑类似，指定用规定的元素来凑齐指定的数目，不同点在于“找零钱”问题中的零钱可以无限次使用，
而此题的每一个元素只能使用一次。采样动态规划的思想，状态转移方程：dp(k, m, n) = max(dp(k-1, m-x, n-y)+1, dp(k-1, m, n))
*/

#include <iostream>
#include <vector>
#include <string>

int countZeroElementOfStr(std::string& str) {
	int zero_elem_count = 0;
	for (int i = 0; i < str.length(); ++i) {
		// std::cout << str[i];
		if (str[i] == '0') {
			zero_elem_count += 1;
		}
	}
	// std::cout << std::endl;
	return zero_elem_count;
}

// TODO: 取出重叠运算
int recursive(std::vector<std::string>& strs, int index, int m, int n) {
	if (index < 0 || index >= strs.size()) {
		return -1;
	}
	std::string cur_elem = strs[index];
	int zero_count = countZeroElementOfStr(cur_elem);
	int one_count = cur_elem.length() - zero_count;
	std::cout << "elem " << cur_elem << " zero_count: " << zero_count << " one_count: " << one_count << std::endl; 
	std::cout << "elem " << cur_elem << " m: " << m << " n: " << n << std::endl;   
	if (zero_count == m && one_count == n) {
		return 1;
	// 加入当前元素后溢出，则直接进入下一个元素
	}else if (zero_count > m || one_count > n) {
		return recursive(strs, index-1, m , n);
	// 加入当前元素后还存在差值，更新差值进入下一个元素
	}else {
		if (index == 0) {
			return -1;
		}
		int sub_len = recursive(strs, index-1, m - zero_count, n - one_count);
		return  sub_len > 0 ? sub_len + 1 : -1;
	}
}

int findMaxForm(std::vector<std::string>& strs, int m, int n) {
	int arr_size = strs.size();
	int max_len = 0;
	for (int i = 0; i < arr_size; ++i) {
		max_len = std::max(max_len, recursive(strs, i, m, n));
	}
	return max_len;
}

int main(int argc, const char * argv[]) {
	// std::vector<std::string> strs = {"10","0001","111001","1","0"};
	// int m = 5;
	// int n = 3;
	std::vector<std::string> strs = {"10","0","1"};
	int m = 1;
	int n = 1;
	int max_len = findMaxForm(strs, m, n);
	std::cout << "find max form: " << max_len << std::endl;
 	return 0;
}