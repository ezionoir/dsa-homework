#include <string>
#include <vector>
using namespace std;

//https://cp-algorithms.com/string/prefix-function.html#implementation
vector<int> kmpTable(string pattern) {
	vector<int> pi(pattern.length());
	for (int i = 1; i < pattern.length(); i++) {
		int j = pi[i-1];
		while (j > 0 && pattern[i] != pattern[j])
			j = pi[j-1];
		if (pattern[i] == pattern[j])
			j++;
		pi[i] = j;
	}
	return pi;
}

//https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
vector<int> searchKnuthMorrisPratt(string text, string pattern) {
	vector<int> matchIndices;
	int textLength = text.length();
	int patternLength = pattern.length();

	vector<int> prefix = kmpTable(pattern);

	int i = 0;
	int j = 0;
	while ((textLength - i) >= (patternLength - j)) {
		if (pattern[j] == text[i]) {
			j++;
			i++;
		}
		if (j == patternLength) {
			matchIndices.push_back(i - j);
			j = prefix[j - 1];
		}
		else if (i < textLength && pattern[j] != text[i]) {
			if (j != 0)
				j = prefix[j - 1];
			else
				i = i + 1;
		}
	}
	return matchIndices;
}