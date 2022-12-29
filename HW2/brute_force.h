#include <string>
#include <vector>
using namespace std;

vector<int> searchBruteForce(string text, string pattern) {
	vector<int> matchIndices; //Hold the start position of matches;
	int textLength = text.length();
	int patternLength = pattern.length();
	for (int i = 0; i <= (textLength - patternLength); i++) {
		int j = 0;
		//Check each character in pattern;
		while (j < patternLength && text[i + j] == pattern[j])
			j++;
		if (j == patternLength) //match
			matchIndices.push_back(i);
	}
	return matchIndices;
}