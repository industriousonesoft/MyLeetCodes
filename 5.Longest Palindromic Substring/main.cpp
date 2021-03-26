#include <iostream>
#include <string>
#include <vector>

// DP fomular: LP[i][j] = LP[i+1][j-1]
// Solution-01: Bottom-Up Approach
std::string longestPalindrome(std::string& str) {
	int size = str.size();
	std::vector<std::vector<int>> dp_table(size, std::vector<int>(size, 0));
	for (int i = 0; i < size; i++) {
		dp_table[i][i] = 1;
	}
	int max_l = 0;
	int max_r = 0;
	for (int len = 2; len <= size; len++) {
		for (int l = 0; l < size - len + 1; l++) {
			int r = l + len - 1;
			if (str[l] == str[r]) {
				// std::cout << "str[" << l << "]: " << str[l] << " - str[" << r << "]: " << str[r] << std::endl; 
				if (len == 2) {
					dp_table[l][r] = 2;
				// Make sure the substring is palindromic
				}else if (dp_table[l+1][r-1] > 0) {
					dp_table[l][r] = dp_table[l+1][r-1] + 2;
				}
				if (dp_table[l][r] > dp_table[max_l][max_r]) {
					max_l = l;
					max_r = r;
					// std::cout << "max_l: " << max_l << " - max_r: " << max_r << std::endl;
				}
			}
		}
	}
	return str.substr(max_l, max_r - max_l + 1);
}

int main(int argc, const char * argv[]) {
	std::string str = "aacabdkacaa";
	std::string result = longestPalindrome(str);
	std::cout << "longest palindrome: " << result << std::endl;
	return 0;
}