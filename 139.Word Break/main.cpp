/*
Given a string s and a dictionary of strings wordDict, return true if s can be segmented 
into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:
Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:
Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.

Example 3:
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
 

Constraints:

1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-break
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// 时间复杂度：O(n^2) 空间复杂度：O(n)
bool wordBreak(string s, vector<string>& wordDict) {
	unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
	int n = s.length();
	// dp[i]记录长度为0~i的子串是否可匹配
	bool dp[n+1];
	memset(dp, false, sizeof(dp));
	// 空串一定可匹配
	dp[0] = true;
	// 遍历字符串s，l和r分别标识子串的首位下标
	for (int r = 0; r < n; ++r)
	{
		for (int l = 0; l <= r; ++l)
		{
			if (dp[l] && wordSet.count(s.substr(l, r - l + 1)) > 0) {
				dp[r+1] = true;
			}
		}
	}
	return dp[n];
}

bool wordBreak2(string s, vector<string>& wordDict) {
	unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
	int n = s.length();
	// dp[i]记录长度为0~i的子串是否可匹配
	bool dp[n+1];
	memset(dp, false, sizeof(dp));
	dp[0] = true;
	int maxWordLength = wordDict[0].length();
	int minWordLength = maxWordLength;
	for (int i = 1; i < wordDict.size(); i++) {
		auto word = wordDict[i];
		maxWordLength = max(maxWordLength, int(word.length()));
		minWordLength = min(minWordLength, int(word.length()));
	}
	// 遍历字符串s，l和r分别标识子串的首位下标
	for (int r = minWordLength - 1; r < n; ++r)
	{
		for (int l = max(0, r-maxWordLength); l <= r; ++l)
		{
			if (dp[l] && wordSet.count(s.substr(l, r - l + 1)) > 0) {
				dp[r+1] = true;
			}
		}
	}
	return dp[n];
}

int main(int argc, const char* argv[]) {
	string s = "catsandog";
	vector<string> wordDict = {"cats","dog","sand","and","cat"};
	string ret = wordBreak2(s, wordDict) ? "true" : "false";
	cout << "word break: " << ret << endl;
	return 0;
}

