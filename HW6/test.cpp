//This file is for testing purpose and is not required in Homework instruction

#include "multilist.h"
#include <iostream>
using namespace std;

int menuCmd(List *L, int option) {
	int index, data;
	switch (option) {
		case 0:
			removeList(L);
			return 0;
		case 1:
			cout << "Index = ";
			cin >> index;
			cout << "Data = ";
			cin >> data;
			add(L, index, data);
			break;
		case 2:
			cout << "Index = ";
			cin >> index;
			cout << "Data = ";
			cin >> data;
			remove(L, index, data);
			break;
		case 3:
			cout << "Index = ";
			cin >> index;
			pop(L, index);
			break;
	}
	printList(L);
	return 1;
}
 
int main() {
	List *L = createList();
	int option = 0;
	do {
		cout << "0: Quit" << endl;
		cout << "1: add" << endl;
		cout << "2: remove" << endl;
		cout << "3: pop" << endl;
		cin >> option;
	} while (menuCmd(L, option));
}