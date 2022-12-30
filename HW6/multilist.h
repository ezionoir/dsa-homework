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
	//current && !previous : current points to the head
	//!current && previous : cant find node
	//!current && !previous : list is empty
	//current && previous : found the node and its predecessor 
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

//This function create index if it doesn't exist
Node* getIndex(List *L, int index) {
	NodePair np = findIndex(L, index);
	Node *ind = np.current;
	if (ind) return ind; //index exists
	//Else create index
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

//Remove members too to avoid leaking memory
void removeIndex(List *L, NodePair np) {
	removeMembers(np.current);
	if (!np.previous) //The index is the head
		L->head = np.current->nextIndex;
	else //Some other index
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
	if (np.current) { //found index
		return memberSize(np.current);
	}
	return 0;
}

void add(List *L, int index, int data) {
	Node *ind = getIndex(L, index);
	Node *nd = createNode(data);
	//addHead
	nd->nextMember = ind->nextMember;
	ind->nextMember = nd;
}

//Remove the first occurence of data in an index
void remove(List *L, int index, int data, bool removeOnEmptied = 1) {
	NodePair np = findIndex(L, index);
	if (!np.current) return; //not found the index
	bool found = 0; //whether data is present in List's index' elements
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
		if (removeOnEmptied) //remove whole index if it is empty after member removal
			if (memberSize(np.current) == 0)
				removeIndex(L, np);
	}
}

//Get and remove the last element of an index
int pop(List *L, int index, bool removeOnEmptied = 1) {
	NodePair np = findIndex(L, index);
	Node *prev = np.current;
	Node *ptr = np.current->nextMember;
	while (ptr->nextMember) {
		prev = ptr;
		ptr = ptr->nextMember;
	}
	prev->nextMember = nullptr;
	int res = ptr->key;
	delete ptr;
	if (removeOnEmptied) //remove whole index if it is empty after member removal
		if (memberSize(np.current) == 0)
			removeIndex(L, np);
	return res;
}

//Remove first occurence of data in all indices
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

void clearList(List *L) {
	//Remove each index (and each member too) until list is empty 
	while (!isEmpty(L)) {
		removeIndex(L, L->head->key);
	}
}

void removeList(List *&L) {
	clearList(L);
	delete L;
	L = nullptr;
}

void printList(List *L) {
	Node *ptr = L->head;
	while (ptr) {
		//Print index
		cout << ptr->key << ": ";
		//Print member
		printMembers(ptr);
		cout << endl;
		//Next index
		ptr = ptr->nextIndex;
	}
}