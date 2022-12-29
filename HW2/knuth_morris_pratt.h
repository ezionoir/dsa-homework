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
	vector<int> matchIndices; //Hold the start position of matches;
	int textLength = text.length();
	int patternLength = pattern.length();

	//Preprocessing
	vector<int> prefix = kmpTable(pattern);

	int textIndex = 0;
	int patternIndex = 0;
	while ((textLength - textIndex) >= (patternLength - patternIndex)) {
		if (pattern[patternIndex] == text[textIndex]) {
			patternIndex++;
			textIndex++;
		}
		if (patternIndex == patternLength) { //there's a match
			matchIndices.push_back(textIndex - patternIndex);
			patternIndex = prefix[patternIndex - 1];
		}
		else if (textIndex < textLength && pattern[patternIndex] != text[textIndex]) {
			if (patternIndex != 0)
				patternIndex = prefix[patternIndex - 1];
			else
				textIndex = textIndex + 1;
		}
	}
	return matchIndices;
}