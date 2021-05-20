/*
We can scramble a string s to get a string t using the following algorithm:

If the length of the string is 1, stop.
If the length of the string is > 1, do the following:
Split the string into two non-empty substrings at a random index, i.e., if the string is s, divide it to x and y where s = x + y.
Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this step, s may become s = x + y or s = y + x.
Apply step 1 recursively on each of the two substrings x and y.
Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.

 

Example 1:

Input: s1 = "great", s2 = "rgeat"
Output: true
Explanation: One possible scenario applied on s1 is:
"great" --> "gr/eat" // divide at random index.
"gr/eat" --> "gr/eat" // random decision is not to swap the two substrings and keep them in order.
"gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both substrings. divide at ranom index each of them.
"g/r / e/at" --> "r/g / e/at" // random decision was to swap the first substring and to keep the second substring in the same order.
"r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively, divide "at" to "a/t".
"r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substrings in the same order.
The algorithm stops now and the result string is "rgeat" which is s2.
As there is one possible scenario that led s1 to be scrambled to s2, we return true.
Example 2:

Input: s1 = "abcde", s2 = "caebd"
Output: false
Example 3:

Input: s1 = "a", s2 = "a"
Output: true
 

Constraints:

s1.length == s2.length
1 <= s1.length <= 30
s1 and s2 consist of lower-case English letters.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/scramble-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include<iostream>
#include<string>

using namespace std;

// 时间复杂度O(2^n)
// 空间复杂度O(n)，map是常量数组不会随着n的变化而变化，空间复杂度来源于递归
bool isScramble(string s1, string s2) {
	if (s1.size() != s2.size()) return false;
	if (s1 == s2) return true;
	int size = s1.size();
	int map[26] = { 0 };
	// 比较s1,s2是否包含相同的字符集
	for (int i = 0; i < size; ++i)
	{
		map[s1[i] - 'a']++;
		map[s2[i] - 'a']--;
	}
	for (int i = 0; i < 26; ++i)
	{
		if (map[i] != 0) return false;
	}

	// 拆分当前子串，以长度为拆分基准，范围为1~size-1
	// 因为拆分后的子串是可以互换的，因此每个长度存在两种有效的拆分方式：
	//	1. 0-len-size
	//	2. 0-(size-len)-size
	for (int len = 1; len < size; ++len)
	{
		// 拆分方式1
		string s1_left = s1.substr(0,len);
		string s1_right = s1.substr(len);
		string s2_left = s2.substr(0, len);
		string s2_right = s2.substr(len);
		if (isScramble(s1_left, s2_left) && isScramble(s1_right, s2_right)) return true;
		// 拆分方式2
		s2_left = s2.substr(0, size - len);
		s2_right = s2.substr(size - len);
		if (isScramble(s1_left, s2_right) && isScramble(s1_right, s2_left)) return true;
	}
	return false;
}

// 包含26个素数的数组，之所以使用素数是为了表示每一个字母的原子性
static constexpr int p[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

bool isScrambleWithPrimeSet(string s1, string s2) {
	if (s1.size() != s2.size()) return false;
	if (s1 == s2) return true;
	int size = s1.size();
	long s1_left_hash = p[s1[0]-'a'];
	long s2_left_hash = p[s2[0]-'a'];
	long s2_right_hash = p[s2[size-1-0]-'a'];
	for (int len = 1; len < size; ++len)
	{
		// 拆分方式1
		string s1_left = s1.substr(0,len);
		string s1_right = s1.substr(len);
		string s2_left = s2.substr(0, len);
		string s2_right = s2.substr(len);
		// 只比较了s1，s2左边的hash值，s1右边的字符集是否与s2右边的字符集匹配则留在下一次递归中检测
		if (s1_left_hash == s2_left_hash && isScramble(s1_left, s2_left) && isScramble(s1_right, s2_right)) return true;
		// 拆分方式2
		s2_left = s2.substr(0, size - len);
		s2_right = s2.substr(size - len);
		// 同理比较了半边的字符集
		if (s1_left_hash == s2_right_hash && isScramble(s1_left, s2_right) && isScramble(s1_right, s2_left)) return true;
		// 更新hash值
		s1_left_hash *= p[s1[len]-'a'];
		s2_left_hash *= p[s2[len]-'a'];
		s2_right_hash *= p[s2[size-len-1]-'a'];
	}
	return false;
}

// 采用动态规划的方式解题： 时间复杂度O(n^4), 空间复杂度O(n^3)
// 使用一个三维数据dp[i][j][len]表示从s1起点为i长度为len和s2起点为j长度为len的两个子串是否是scambling，如果是为true，反之为false
// 对于某个len值，只要存在一种切割方式能够s1.substr(i,len)和s2.substr(j,len)满足scrambling即可
bool isScrambleDP(string s1, string s2) {
	if (s1.size() != s2.size()) return false;
    if (s1 == s2) return true;
    int n = s1.size();
    bool dp[n][n][n+1];
    memset(dp, false, sizeof(dp));
    for (int len = 1; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            for (int j = 0; j <= n - len; ++j) {
                if (len == 1) {
                    dp[i][j][1] = s1[i] == s2[j];
                } else {
                	// 遍历切割方式，k表示每次切割的长度，寻找一种能满足s1和s2子串满足scraling的切割方式即可
                    for (int k = 1; k < len; ++k) {
                        if ((dp[i][j][k] && dp[i + k][j + k][len - k])/* ss1左与ss2左，ss1右与ss2右比较 */ || 
                        	(dp[i + k][j][len - k] && dp[i][j + len - k][k])/* ss1左与ss2右，ss1左与ss2右比较 */ ) {
                            dp[i][j][len] = true;
                            break;
                        }
                    }
                }                
            }
        }
    }
    return dp[0][0][n];
}


int main(int argc, const char* argv[]) {
	string s1 = "great";
	string s2 = "rgeat";
	cout << s1 << " and " << s2 <<" is scramble: ";
	isScrambleDP(s1, s2) ? (cout << "true") : (cout << "false");
	cout << endl;
	return 0;
}