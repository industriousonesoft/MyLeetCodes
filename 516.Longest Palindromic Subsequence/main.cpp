/*
Given a string s, find the longest palindromic subsequence's length in s.

A subsequence is a sequence that can be derived from another sequence by deleting some 
or no elements without changing the order of the remaining elements.


Example 1:

Input: s = "bbbab"
Output: 4
Explanation: One possible longest palindromic subsequence is "bbbb".
Example 2:

Input: s = "cbbd"
Output: 2
Explanation: One possible longest palindromic subsequence is "bb".
 

Constraints:

1 <= s.length <= 1000
s consists only of lowercase English letters.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-palindromic-subsequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
DP formula: 0 < i,j < s.size()
    if s[i] == s[j]; then 
        L(i,j) = L(i+1,j-1) + 2
    else 
        L(i,j) = max(L(i+1, j), L(i, j-1))
*/

#include <iostream>
#include <string>
#include <vector>

// Solutions-1: Top-Down Approach
// Time Complexity: O(n^2),
// 时间复杂度计算：所有需要计算的坐标对应于一个NxN的二维数组，维度为L，R，以L和R维度各扫描一遍二维数组的时间复杂度是O(n^2)，
// 因此不加备忘录的情况下时间复杂度是O(n^4)，加备忘录的情况下复杂度是O(n^2)
// Space Commplexity: O(n^2)
int recur(std::string& s, int l, int r, int** memo_table) {
    int len = 0;
    if (l > r || r < l) {
        return 0;
    }else if (memo_table[l][r] > 0) {
    	return memo_table[l][r];
    }else if (l == r) {
        len = 1;
    }else if (s[l] == s[r]) {
        len = recur(s, l+1, r-1, memo_table) + 2;
    }else {
        len = std::max(recur(s, l+1, r, memo_table), recur(s, l, r-1, memo_table));
    }
    memo_table[l][r] = len;
//    std::cout<< "l:" << l <<",r" << r << " = "<< len << std::endl;
    return len;
}

int recurLongestPalindromeSubseq(std::string& s) {
	int size = s.size();
//	std::cout << "size: " << size << std::endl;
    // std::vector<std::vector<int>> memo_table(size, std::vector<int>(size,0));
    // 使用指针间接引用创建二维数组
    // 首先创建若干个大小一致的动态数组，然后将这些数组的首地址(转化为指针)按顺序存储到一个动态数组中，就相当于模拟了一个二维动态数组。
    // 由于低一级的数组是分开创建的，所以整个二维数组的内存不连续。
    int** memo_table = new int*[size];
    return recur(s, 0, size-1, memo_table);
}

// Solution-02: Down-Up Approach
int dpLongestPalindromeSubSeq(std::string& s) {
    int size = s.size();
    int dp_table[size][size];
    memset(dp_table, 0, sizeof(dp_table));
    for (int i = 0; i < size; ++i) {
        dp_table[i][i] = 1;
    }
    // 解题思路：将原序列拆分成长度不同的子序列，从长度小的序列开始搜索回文序列
    for (int len = 2; len <= size; ++len) {
        for (int l = 0; l < size - len + 1; ++l) {
            int r = l + len - 1;
            if (s[l] == s[r]) {
                dp_table[l][r] = len == 2 ? 2 : dp_table[l+1][r-1] + 2;
            }else {
                dp_table[l][r] = std::max(dp_table[l+1][r], dp_table[l][r-1]);
            }
        }
    }
    return dp_table[0][size-1];
}

int main(int argc, const char * argv[]) {
    // std::string str = "BBABCBCAB";
   // std::string str = "bbbab";
     std::string str = "euazbipzncptldueeuechubrcourfpftcebikrxhybkymimgvldiwqvkszfycvqyvtiwfckexmowcxztkfyzqovbtmzpxojfofbvwnncajvrvdbvjhcrameamcfmcoxryjukhpljwszknhiypvyskmsujkuggpztltpgoczafmfelahqwjbhxtjmebnymdyxoeodqmvkxittxjnlltmoobsgzdfhismogqfpfhvqnxeuosjqqalvwhsidgiavcatjjgeztrjuoixxxoznklcxolgpuktirmduxdywwlbikaqkqajzbsjvdgjcnbtfksqhquiwnwflkldgdrqrnwmshdpykicozfowmumzeuznolmgjlltypyufpzjpuvucmesnnrwppheizkapovoloneaxpfinaontwtdqsdvzmqlgkdxlbeguackbdkftzbnynmcejtwudocemcfnuzbttcoew";
    int len = recurLongestPalindromeSubseq(str);
     // int len = dpLongestPalindromeSubSeq(str);

    std::cout << " longest palindrome sebsequence: " << len << std::endl;
    return 0;
}

