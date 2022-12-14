#include "circular_linked_list.h"
#include <iostream>
using namespace std;

bool isEmpty(List *L) {
	return L->head == NULL;
}

List* createList() {
	List *L = new List;
	L->head = L->tail = NULL;
	return L;
}

Node* createNode(int data) {
	Node *nd = new Node;
	nd->key = data;
	nd->next = NULL;
	return nd;
}

bool addHead(List *L, int data) {
	if (isEmpty(L)) {
		Node *nd = createNode(data);
		nd->next = nd;
		L->head = L->tail = nd; //1 element list
		return 1;
	} //else
	Node *nd = createNode(data);
	nd->next = L->head;
	L->tail->next = nd;
	L->head = nd;
	return 1;
}

bool addTail(List *L, int data) {
	if (isEmpty(L)) //When empty head is the same as tail
		return addHead(L, data);
	Node *nd = createNode(data);
	nd->next = L->tail->next;
	L->tail->next = nd;
	L->tail = nd;
	return 1;
}

void removeHead(List *L) {
	if (isEmpty(L)) return;
	Node *rmv = L->head;
	if (L->head == L->tail) { //1 element list
		L->head = L->tail = NULL;
	}
	else { //Head is now the element next to it
		L->tail->next = L->head->next;
		L->head = L->tail->next;
	}
	delete rmv;
}

void removeTail(List *L) {
	if (isEmpty(L)) return;
	if (L->head == L->tail) { //When list has 1 element head is the same as tail
		return removeHead(L);
	}
	Node *ptr = L->head;
	//Finding node right before tail
	while (ptr->next != L->tail) {
		ptr = ptr->next;
	}
	L->tail = ptr;
	delete ptr->next;
	ptr->next = L->head;
}

Node* findNode(List *L, int data) {
	if (isEmpty(L)) return NULL;
	Node *ptr = L->head;
	do {
		if (ptr->key == data) return ptr;
		ptr = ptr->next;
	} while (ptr != L->tail->next); //until head is not head (done 1 cycle)
	return NULL;
}

bool addAfter(List *L, int data, int val) {
	if (isEmpty(L)) return 0;
	Node *nd = findNode(L, val);
	if (!nd) return 0;
	if (nd == L->tail) //addAfter tail is the same as addTail
		return addTail(L, data);
	Node *after = createNode(data);
	after->next = nd->next;
	nd->next = after;
	return 1;
}

void removeAfter(List *L, int val) {
	if (isEmpty(L)) return;
	Node *nd = findNode(L, val);
	//Remove after tail is defined as invalid even though the list is circular (struct member next gave the nodes a sense of direction, thus the next of tail is meaningless)
	if (!nd || nd == L->tail) return;
	if (nd->next == L->tail)
		return removeTail(L);
	Node *after = nd->next;
	nd->next = after->next;
	delete after;
}

void printList(List *L) {
	if (isEmpty(L)) {
		cout << "Empty" << endl;
		return;
	}
	Node *ptr = L->head;
	do {
		cout << ptr->key << " ";
		ptr = ptr->next;
	} while (ptr != L->tail->next); //until head is not head (done 1 cycle)
	cout << endl;
}

void removeList(List *&L) {
	//Remove each first element until empty
	while (!isEmpty(L))
		removeHead(L);
	delete L;
	L = NULL;
}