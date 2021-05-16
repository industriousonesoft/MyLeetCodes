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

bool isScramble(string s1, string s2) {
	if (s1.size() != s2.size()) return false;
	if (s1 == s2) return true;
	int size = s1.size();
	int map[size];
	memset(map,0,sizeof(map));
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

	for (int len = 1; len < size; ++len)
	{
		string s1_left = s1.substr(0,len);
		string s1_right = s1.substr(len);
		if (isScramble(s1_left, s2.substr(0,len)) && isScramble(s1_right, s2.substr(len))) 
			return true;
		if (isScramble(s1_left, s2_right) && isScramble(s1_right, s2_left)) 
			return true;
	}
	return false;
}

int main(int argc, const char* argv[]) {
	string s1 = "great";
	string s2 = "rgeat";
	cout << s1 << " and " << s2 <<" is scramble: ";
	isScramble(s1, s2) ? (cout << "true") : (cout << "false");
	cout << endl;
	return 0;
}