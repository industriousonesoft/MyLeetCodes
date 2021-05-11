/*
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character
 

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Example 2:
Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
 

Constraints:

0 <= word1.length, word2.length <= 500
word1 and word2 consist of lowercase English letters.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/edit-distance
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#include <iostream>
#include <string>

using namespace std;

/*
题解：采样动态规划思维，两个原字符串的编辑距离最优解可分解为二者子串之间的编辑距离最优解
用dp[i][j]表示word1长度为i的子串编辑成word2长度为j的子串需要的最小操作步骤数，因此
dp[0][0] = 0
dp[0][j] = j, j > 0
dp[i][0] = i, i > 0
word1[i-1] != word2[j-1], dp[i][j] = min(dp[i-1][j-1] + (word1[i-1] == word2[j-1] ? 0 : 1) /* 相等时不做任何操作，不相等时执行替换操作 */, dp[i-1][j] + 1 /* 执行插入操作 */, dp[i][j-1] + 1 /* 执行删除操作 */)

*/

int editDistance(string word1, string word2) {

    return 0;
}

int main(int argc, const char* argv[]) {
    return 0;
}