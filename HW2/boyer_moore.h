#include <string>
#include <vector>
using namespace std;

#define CHAR_RANGE 256

int max(int a, int b) {
	return a > b ? a : b;
}
//https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/
vector<int> searchBoyerMoore(string text, string pattern) {
	vector<int> matchIndices; //Hold the start position of matches;
	int textLength = text.length();
	int patternLength = pattern.length();

	//Preprocessing
	vector<int> badChars(CHAR_RANGE, -1); //default all to -1
	for (int i = 0; i < pattern.size(); i++)
		badChars[(int)pattern[i]] = i;

	int shift = 0;
	while(shift <= (textLength - patternLength)) {
		int j = patternLength - 1;
		//matching pattern and text at position shift
		while(j >= 0 && pattern[j] == text[shift + j])
			j--;
		if (j < 0) { //Whole match
			matchIndices.push_back(shift);
			if ((shift + patternLength) < textLength)
				shift += patternLength - badChars[text[shift + patternLength]];
			else shift++;
		}
		else
			shift += max(1, j - badChars[text[shift + j]]);
	}
	return matchIndices;
}