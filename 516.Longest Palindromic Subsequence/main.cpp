/*
 * @Description: 
 * @Version: 
 * @Author: CaoWanPing
 * @Date: 2021-03-24 18:23:49
 * @LastEditTime: 2021-03-24 20:32:58
 */
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

// Solutions-1: Recursive
// Time Complexity: O(n^2) How to estimate this value?
// Space Commplexity: O(n^2)
int recur(std::string& s, int l, int r, std::vector<std::vector<int>>& memo_table) {
    int len = 0;
    // Invailed 
    if (l == r){
        len = 1;
    }else if (s[l] == s[r]) {
        int next = memo_table[l+1][r-1];
        if (next > 0) {
            return next + 2;
        }else {
            len = recur(s, l+1, r-1, memo_table) + 2;
        }
    }else {
        int next_l = memo_table[l+1][r];
        int next_r = memo_table[l][r-1];
        std::cout << "memo[" << l+1 << "][" << r << "] = " << next_l << std::endl;
        std::cout << "memo[" << l << "][" << r-1 << "] = " << next_r << std::endl;
        len = std::max(next_l > 0 ? next_l : recur(s, l+1, r, memo_table), next_r > 0 ? next_r : recur(s, l, r-1, memo_table));
    }
    if (len > 0) {
        memo_table[l][r] = len;
        std::cout << "new memo[" << l << "][" << r << "] = " << len << std::endl;
    }
    return len;
}

int recurLongestPalindromeSubseq(std::string s) {
    std::vector<std::vector<int>> memo_table(s.size(), std::vector<int>(s.size(),0));
    return recur(s, 0, s.size()-1, memo_table);
}

// Solution-02: Dynamic Programming
int dpLongestPalindromeSubSeq(std::string s) {
    int l,r = -1;
    std::vector<std::vector<int>> dp_table(s.size(), std::vector<int>(s.size(),0));
    if (s.size() % 2 == 0) {
        r = s.size() / 2;
        l = r - 1;
        dp_table[l][r] = s[l] == s[r] ? 1 : 0;
    }else {
        l = r = s.size() / 2;
        dp_table[l][r] = 1;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    // std::string str = "BBABCBCAB";
    std::string str = "euazbipzncptldueeuechubrcourfpftcebikrxhybkymimgvldiwqvkszfycvqyvtiwfckexmowcxztkfyzqovbtmzpxojfofbvwnncajvrvdbvjhcrameamcfmcoxryjukhpljwszknhiypvyskmsujkuggpztltpgoczafmfelahqwjbhxtjmebnymdyxoeodqmvkxittxjnlltmoobsgzdfhismogqfpfhvqnxeuosjqqalvwhsidgiavcatjjgeztrjuoixxxoznklcxolgpuktirmduxdywwlbikaqkqajzbsjvdgjcnbtfksqhquiwnwflkldgdrqrnwmshdpykicozfowmumzeuznolmgjlltypyufpzjpuvucmesnnrwppheizkapovoloneaxpfinaontwtdqsdvzmqlgkdxlbeguackbdkftzbnynmcejtwudocemcfnuzbttcoew";
    int len = recurLongestPalindromeSubseq(str);

    std::cout << " longest palindrome sebsequence: " << len << std::endl;
    return 0;
}

