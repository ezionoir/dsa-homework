//This file is for demonstration purpose and is not required in Homework instruction

#include "circular_linked_list.h"
#include <iostream>
using namespace std;

int menuCmd(List *L, int option) {
	int data, val;
	switch (option) {
		case 0:
			removeList(L);
			return 0;
		case 1:
			cout << "Data = ";
			cin >> data;
			addHead(L, data);
			break;
		case 2:
			cout << "Data = ";
			cin >> data;
			addTail(L, data);
			break;
		case 3:
			removeHead(L);
			break;
		case 4:
			removeTail(L);
			break;
		case 5:
			cout << "Data = ";
			cin >> data;
			cout << "Val = ";
			cin >> val;
			addAfter(L, data, val);
			break;
		case 6:
			cout << "Val = ";
			cin >> val;
			removeAfter(L, val);
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
		cout << "1: addHead" << endl;
		cout << "2: addTail" << endl;
		cout << "3: removeHead" << endl;
		cout << "4: removeTail" << endl;
		cout << "5: addAfter" << endl;
		cout << "6: removeAfter" << endl;
		cin >> option;
	} while (menuCmd(L, option));
}