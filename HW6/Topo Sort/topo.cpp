#include <vector>
#include <fstream>
#include <iostream>
#include "../multilist.h"
using namespace std;

int main() {
	//Read from file
	ifstream inputFile("input.txt");
	int a, b;
	vector<int> num; //vector of pair a < b (< : topologically)
	while (inputFile.peek() != EOF) {
		inputFile.get(); // (
		inputFile >> a;
		inputFile.get(); // ,
		inputFile >> b;
		inputFile.get(); // )
		num.push_back(a);
		num.push_back(b);
	}

	//Create list to store topology requirement
	List *L = createList();
	for (int i = 0; i < num.size(); i+=2)
		add(L, num[i + 1], num[i]); //num[i] < num[i + 1] (< : topologically)
	for (int i = 0; i < num.size(); i+=2)
		if (memberSize(L, num[i]) == 0)
			add(L, num[i], -1); //valid number must be positive, thus -1 was chosen as placeholder
	removeAll(L, -1, 0); //now only the index exist (removeOnEmptied set to false)

	//printList(L); // Index: member[] means that each member < index (< : topologically)

	//Sort
	while (!isEmpty(L)) {
		Node *ptr = L->head;
		while (ptr) {
			if (memberSize(ptr) == 0) { //There's no number less than ptr->key in topology sense
				cout << ptr->key << " ";
				removeAll(L, ptr->key, 0); //Remove all ocurences of ptr->key after it is printed out (removeOnEmptied set to false)
				removeIndex(L, ptr->key);
			}
			ptr = ptr->nextIndex;
		}
	}
	cout << endl;
	removeList(L);
}