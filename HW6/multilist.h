#include <iostream>
using namespace std;

struct Node {
	int key;
	Node *nextMember;
	Node *nextIndex;
};

struct List {
	Node *head;
};

struct NodePair {
	Node *previous;
	Node *current;
	//current && !previous : head
	//!current && previous : not found
	//!current && !previous : empty
	//current && previous : found pair 
};

Node* createNode(int key) {
	Node *nd = new Node;
	nd->key = key;
	nd->nextMember = nullptr;
	nd->nextIndex = nullptr;
	return nd;
};

int isEmpty(List *L) {
	return L->head == nullptr;
}

NodePair findIndex(List *L, int index) {
	NodePair np = {0};
	if (isEmpty(L)) return np;
	Node *ptr = L->head;
	while (ptr) {
		if (ptr->key == index) {
			np.current = ptr;
			break;
		}
		np.previous = ptr;
		ptr = ptr->nextIndex;
	}
	return np;
}

Node* getIndex(List *L, int index) {
	NodePair np = findIndex(L, index);
	Node *ind = np.current;
	if (ind) return ind;
	Node *nd = createNode(index);
	nd->nextIndex = L->head;
	L->head = nd;
	return nd;
}

void removeMembers(Node *index) {
	Node *ptr = index->nextMember;
	while (ptr) {
		Node *del = ptr;
		ptr = ptr->nextMember;
		delete del;
	}
	index->nextMember = nullptr;
}

void printMembers(Node *index) {
	Node *ptr = index->nextMember;
	while (ptr) {
		cout << ptr->key << " ";
		ptr = ptr->nextMember;
	}
}

void removeIndex(List *L, NodePair np) {
	removeMembers(np.current);
	if (!np.previous) //found and it is the head
		L->head = np.current->nextIndex;
	else //found and it is not the head
		np.previous->nextIndex = np.current->nextIndex;
	delete np.current;
}

void removeIndex(List *L, int index) {
	if (isEmpty(L)) return;
	NodePair np = findIndex(L, index);
	if (!np.current) return; //not found
	removeIndex(L, np);
}

int memberSize(Node *index) {
	int count = 0;
	Node *ptr = index->nextMember;
	while (ptr) {
		count++;
		ptr = ptr->nextMember;
	}
	return count;
}

int memberSize(List *L, int index) {
	NodePair np = findIndex(L, index);
	if (np.current) {
		return memberSize(np.current);
	}
	return 0;
}

void add(List *L, int index, int data) {
	Node *ind = getIndex(L, index);
	Node *nd = createNode(data);
	nd->nextMember = ind->nextMember;
	ind->nextMember = nd;
}

void remove(List *L, int index, int data, bool removeOnEmptied = 1) {
	NodePair np = findIndex(L, index);
	if (!np.current) return;
	bool found = 0;
	Node *prev = np.current;
	Node *ptr = np.current->nextMember;
	while (ptr) {
		if (ptr->key == data) {
			found = 1;
			break;
		}
		prev = ptr;
		ptr = ptr->nextMember;
	}
	if (found) {
		prev->nextMember = ptr->nextMember;
		delete ptr;
		if (removeOnEmptied)
			if (memberSize(np.current) == 0)
				removeIndex(L, np);
	}
}

void removeAll(List *L, int data, bool removeOnEmptied = 1) {
	Node *ptr = L->head;
	while (ptr) {
		remove(L, ptr->key, data, removeOnEmptied);
		ptr = ptr->nextIndex;
	}
}

List* createList() {
	List *L = new List;
	L->head = nullptr;
	return L;
}

void removeList(List *&L) {
	while (!isEmpty(L)) {
		removeIndex(L, L->head->key);
	}
}

void printList(List *L) {
	Node *ptr = L->head;
	while (ptr) {
		cout << ptr->key << ": ";
		printMembers(ptr);
		cout << endl;
		ptr = ptr->nextIndex;
	}
}