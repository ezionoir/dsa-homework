#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "../multilist.h"
using namespace std;

int getNumIteration(int n, int k) {
	int i = 1;
	if (n < k)
		return 1;
	while (n > (int)pow(k, i))
		i++;
	return i;
}

void radixSort(vector<int> &num, int k) {
	List *L = createList();
	int max = *max_element(num.begin(), num.end());
	for (int d = 0; d < getNumIteration(max, k); d++) {
		for (int i = 0; i < num.size(); i++)
			add(L, (num[i] / (int)pow(k, d)) % k, num[i]); //Add num[i] to its corresponding bucket 
		int ind = 0, n = 0;
		while (ind < k) {
			while (memberSize(L, ind) != 0) //while bucket ind still have number left
				num[n++] = pop(L, ind); //add the last element to the array (in-place)
			ind++;
		}
	}
	removeList(L);
}

int main() {
	//Read from input file
	ifstream inputFile("input.txt");
	int k, n;
	inputFile >> k >> n;
	vector<int> num(n);
	for (int i = 0; i < n; i++)
		inputFile >> num[i];

	//Sort
	radixSort(num, k);

	//Result
	for (int x : num)
		cout << x << " ";
}