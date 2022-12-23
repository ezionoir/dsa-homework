struct Node {
	int key;
	Node *next;
};

struct List {
	Node *head;
	Node *tail;
};


bool isEmpty(List *L);

List* createList();

Node* createNode(int data);

bool addHead(List *L, int data);

bool addTail(List *L, int data);

void removeHead(List *L);

void removeTail(List *L);

Node* findNode(List *L, int data);

bool addAfter(List *L, int data, int val);

void removeAfter(List *L, int val);

void printList(List *L);

void removeList(List *&L);