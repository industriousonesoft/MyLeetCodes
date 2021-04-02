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

using namespace std;
// Solution-01: Up-Down Approach

typedef vector<vector<vector<int>>> MemoTable;

int countZeroElementOfStr(string& str) {
	int zero_elem_count = 0;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == '0') {
			zero_elem_count += 1;
		}
	}
	return zero_elem_count;
}

int recursive(vector<string>& strs, int index, int m, int n, MemoTable& memo_table) {
	if (index < 0) {
		return 0;
	}
	int computed_result = memo_table[index][m][n];
	if ( computed_result >= 0) {
		return computed_result;
	}
	string cur_elem = strs[index];
	int zero_count = countZeroElementOfStr(cur_elem);
	int one_count = cur_elem.length() - zero_count;
	// cout << "elem " << cur_elem << " zero_count: " << zero_count << " one_count: " << one_count << endl; 
	// cout << "elem " << cur_elem << " m: " << m << " n: " << n << endl;   
	int len = 0;
	// 加入当前元素后刚好凑齐
	if (zero_count == m && one_count == n) {
		len = 1;
	// 加入当前元素后还存在差值，更新差值进入下一个元素
	}else if (zero_count <= m && one_count <= n) {
		len = recursive(strs, index-1, m - zero_count, n - one_count, memo_table) + 1;
	}
	// 加入当前元素溢出与将当前的m,n值传递给下一个值这两种情况的操作是一样的
	memo_table[index][m][n] = len;
	return max(len, recursive(strs, index-1, m, n, memo_table));
}

int findMaxForm1(vector<string>& strs, int m, int n) {
	int arr_size = strs.size();
	MemoTable memo_table(arr_size,vector<vector<int>>(m+1, vector<int>(n+1, -1)));
	int max_len = recursive(strs, arr_size-1, m, n, memo_table);
	return max_len;
}

// Resolution-02: Bottom-Up Approach
int findMaxForm2(vector<string>& strs, int m, int n) {
    int dp_table[m+1][n+1];
    memset(dp_table, 0, sizeof(dp_table));

    for(int i = 0; i < strs.size(); i++){
        string s = strs[i];
        int len = s.length();
        int zero_count = 0, one_count = 0;
        
        for(int l = 0; l < len; l++){
            if(s[l] == '0') {
            	zero_count++;
            }
        }
        one_count = len - zero_count;
        // 对数组中的每一个元素做一次<=m, <=n的判断
        for (int j = m; j >= 0; j--){
            for (int k = n; k >=0; k--) {
                if(zero_count <= j && one_count <= k) {
                	// 满足j,k的数组长度 = max(包括当前元素的数组长度, 不包括当前元素且由当前元素之前的元素组成的数组长度）
                    dp_table[j][k] = max(dp_table[j-zero_count][k-one_count]+1, dp_table[j][k]);
                }
            }
        }
    }
    return dp_table[m][n];
}

int main(int argc, const char * argv[]) {
	vector<string> strs = {"10","0001","111001","1","0"};
	int m = 5;
	int n = 3;
	// vector<string> strs = {"10","0","1"};
	// int m = 1;
	// int n = 1;
	// vector<string> strs = {"10","0001","111001","1","0"};
	// int m = 3;
	// int n = 4;
	// vector<string> strs = {"011111","001","001"};
	// int m = 4;
	// int n = 5;
	int max_len = findMaxForm2(strs, m, n);
	cout << "find max form: " << max_len << endl;
 	return 0;
}