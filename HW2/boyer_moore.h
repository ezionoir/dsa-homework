#include <string>
#include <vector>
using namespace std;

#define CHAR_RANGE 256

int max(int a, int b) {
	return a > b ? a : b;
}
//https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/
vector<int> searchBoyerMoore(string text, string pattern) {
	vector<int> matchIndices;
	int textLength = text.length();
	int patternLength = pattern.length();

	vector<int> badChars(CHAR_RANGE, -1);
	for (int i = 0; i < pattern.size(); i++)
		badChars[(int)pattern[i]] = i;

	int s = 0;
	while(s <= (textLength - patternLength)) {
		int j = patternLength - 1;
		while(j >= 0 && pattern[j] == text[s + j])
			j--;
		if (j < 0) {
			matchIndices.push_back(s);
			if ((s + patternLength) < textLength)
				s += patternLength - badChars[text[s + patternLength]];
			else s++;

		}
		else
			s += max(1, j - badChars[text[s + j]]);
	}
	return matchIndices;
}