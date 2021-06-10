xz/*
Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:

Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]
Example 2:

Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
Explanation: Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: []
 

Constraints:

1 <= s.length <= 20
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 10
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-break-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// 时间复杂度：O(n^2), 空间复杂度： O(n)
vector<string> wordBreak(string s, vector<string>& wordDict) {
	unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
	int n = s.length();
	// dp_match[i]表示长度为i的子串是否成功匹配
	bool dpMatch[n+1];
	memset(dpMatch, false, sizeof(dpMatch));
	dpMatch[0] = true;
	int minWordLen = wordDict[0].length();
	int maxWordLen = minWordLen;
	for (int i = 1; i < wordDict.size(); ++i)
	{
		minWordLen = min(minWordLen, (int)wordDict[i].length());
		maxWordLen = max(maxWordLen, (int)wordDict[i].length());
	}
	// dp[i]用于存储长度为i的子串可由wordDict中的子串拼接的所有句子
	vector<vector<string>> dp(n+1, vector<string>());
	for (int r = minWordLen - 1; r < n; r++) {
		for (int l = max(0, r - maxWordLen); l <= r; l++) {
			auto sub_str = s.substr(l, r - l + 1);
			if (dpMatch[l] && wordSet.count(sub_str) > 0) {
				dpMatch[r+1] = true;
				if (l == 0) {
					dp[r+1].push_back(sub_str);
				}else {
					for (auto sent : dp[l]) {
						sent += " " + sub_str;
						dp[r+1].push_back(sent);
					}
				}
			}
		}
	}
	return dp[n];
}

int main(int argc, const char* argv[]) {
	string s = "catsanddog";
	vector<string> wordDict = {"cat","cats","and","sand","dog"};
	auto sentences = wordBreak(s, wordDict);
	for (auto sent : sentences) {
		cout << sent << endl;
	}
	return 0;
}