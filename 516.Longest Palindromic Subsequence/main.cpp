/*
 A subsequence is a sequence that can be derived from another sequence 
 by deleting some or no elements without changing the order of the remaining elements
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
int recur(std::string& s, int l, int r, std::vector<std::vector<int>>& memo_table) {
    int len = 0;
    if (l >= s.size() || r < 0) {
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
    std::vector<std::vector<int>> memo_table(size, std::vector<int>(size,0));
    return recur(s, 0, size-1, memo_table);
}

// Solution-02: Down-Up Approach
int dpLongestPalindromeSubSeq(std::string& s) {
    int size = s.size();
    std::vector<std::vector<int>> dp_table(s.size(), std::vector<int>(size,0));
    for (int i = 0; i < size; ++i) {
        dp_table[i][i] = 1;
    }
    // 解题思路：将原序列划分为多个对称的子序列，然后从各个子序列的对称点向两边扩展，小的子序列的回文序列一定包含于大的子序列中
    return 0;
}

int main(int argc, const char * argv[]) {
//     std::string str = "BBABCBCAB";
//    std::string str = "bbbab";
     std::string str = "euazbipzncptldueeuechubrcourfpftcebikrxhybkymimgvldiwqvkszfycvqyvtiwfckexmowcxztkfyzqovbtmzpxojfofbvwnncajvrvdbvjhcrameamcfmcoxryjukhpljwszknhiypvyskmsujkuggpztltpgoczafmfelahqwjbhxtjmebnymdyxoeodqmvkxittxjnlltmoobsgzdfhismogqfpfhvqnxeuosjqqalvwhsidgiavcatjjgeztrjuoixxxoznklcxolgpuktirmduxdywwlbikaqkqajzbsjvdgjcnbtfksqhquiwnwflkldgdrqrnwmshdpykicozfowmumzeuznolmgjlltypyufpzjpuvucmesnnrwppheizkapovoloneaxpfinaontwtdqsdvzmqlgkdxlbeguackbdkftzbnynmcejtwudocemcfnuzbttcoew";
    int len = recurLongestPalindromeSubseq(str);

    std::cout << " longest palindrome sebsequence: " << len << std::endl;
    return 0;
}

