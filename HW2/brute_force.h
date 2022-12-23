#include <string>
#include <vector>
using namespace std;

vector<int> searchBruteForce(string text, string pattern) {
	vector<int> matchIndices;
	int textLength = text.length();
	int patternLength = pattern.length();
	for (int i = 0; i <= (textLength - patternLength); i++) {
		int j = 0;
		while (j < patternLength && text[i + j] == pattern[j])
			j++;
		if (j == patternLength)
			matchIndices.push_back(i);
	}
	return matchIndices;
}