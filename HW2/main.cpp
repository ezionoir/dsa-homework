#include "brute_force.h"
#include "rabin_karp.h"
#include "knuth_morris_pratt.h"
#include "boyer_moore.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
using namespace std::chrono;
using namespace std;

#define EXIT_OK 0
#define EXIT_IO 1
#define EXIT_ARGV 2

typedef vector<int> (*searchFunction)(string text, string pattern);

searchFunction getSearchFunction(string algorithm) {
	if (algorithm == "BF") return searchBruteForce;
	else if (algorithm == "RK") return searchRabinKarp;
	else if (algorithm == "KMP") return searchKnuthMorrisPratt;
	else if (algorithm == "BM") return searchBoyerMoore;
	else return nullptr;
}

int main(int argc, char const *argv[]) {
	//Read from file input
	ifstream inputFile(argv[1]);
	if (!inputFile) {
		cout << "Failed to open " << argv[1] << endl;
		return EXIT_IO;
	}
	string text;
	getline(inputFile, text);

	string pattern(argv[2]);
	string algorithm(argv[3]);

	searchFunction search = getSearchFunction(algorithm);
	if (!search) { //nullptr
		cout << "Unrecognized algorithm: " << algorithm << endl;
		return EXIT_ARGV;
	}

	//Record execution time
	auto start = high_resolution_clock::now();
	vector<int> matches = search(text, pattern);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start); //millisecond = microsecond / 1000

	cout << matches.size() << " - " << duration.count() / 1000.0 << endl;
	return EXIT_OK;
}