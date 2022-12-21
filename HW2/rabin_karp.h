#include <string>
#include <vector>
using namespace std;

#define RK_BASE 256
#define RK_MODULO 101

//https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/
vector<int> searchRabinKarp(string text, string pattern) {
	vector<int> matchIndices;
	int textLength = text.length();
	int patternLength = pattern.length();

	int patternHash = 0;
	int textHash = 0;
	int hash = 1;

	for (int i = 0; i < patternLength - 1; i++)
		hash = (hash * RK_BASE) % RK_MODULO;

	for (int i = 0; i < patternLength; i++) {
		patternHash = (RK_BASE * patternHash + pattern[i]) % RK_MODULO;
		textHash = (RK_BASE * textHash + text[i]) % RK_MODULO;
	}

	for (int i = 0; i <= textLength - patternLength; i++) {
		if (patternHash == textHash) {
			int j = 0;
			for (; j < patternLength; j++)
				if (text[i + j] != pattern[j])
					break;
			if (j == patternLength)
				matchIndices.push_back(i);
		}
		if (i < textLength - patternLength) {
			textHash = (RK_BASE * (textHash - text[i] * hash) + text[i + patternLength]) % RK_MODULO;
			if (textHash < 0)
				textHash = (textHash + RK_MODULO);
		}
	}

	return matchIndices;
}