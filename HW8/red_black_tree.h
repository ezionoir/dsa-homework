#define BLACK 0
#define RED 1

struct RBNode {
	int key;
	bool color;
	RBNode *parent;
	RBNode *left;
	RBNode *right;
};

//Reference: 
//https://www.programiz.com/dsa/red-black-tree
//The course: Data Structures and Algorithms - University of Science - VNUHCM

RBNode* createNode(int key, bool color, RBNode *nil);

void leftRotate(RBNode *&root, RBNode *x, RBNode *nil);

void rightRotate(RBNode *&root, RBNode *y, RBNode *nil);

void insertBST(RBNode *&root, RBNode *x, RBNode *nil);

void insertAdjustLeft(RBNode *&root, RBNode *&x, RBNode *nil);

void insertAdjustRight(RBNode *&root, RBNode *&x, RBNode *nil);

void insertAdjust(RBNode *&root, RBNode *x, RBNode *nil);

RBNode* succesor(RBNode *x, RBNode *nil);

void removeAdjustLeft(RBNode *&root, RBNode *&x, RBNode *nil);

void removeAdjustRight(RBNode *&root, RBNode *&x, RBNode *nil);

void removeAdjust(RBNode *root, RBNode *x, RBNode *nil);

void printPreOrder(RBNode *root, RBNode *nil);

void printPostOrder(RBNode *root, RBNode *nil);

void printInOrder(RBNode *root, RBNode *nil);

int max(int a, int b);

int nodeHeight(RBNode *x, RBNode *nil);

void removeSubTree(RBNode *&root, RBNode *nil);

void removeTree(RBNode *&root, RBNode *&nil);

void Insert(RBNode *&root, int key, RBNode *nil);

RBNode* createTree(int a[], int n, RBNode *&nil);

RBNode* lookUp(RBNode *root, int key, RBNode *nil);

int Height(RBNode *root);

int BlackHeight(RBNode *root);

int Remove(RBNode *root, int key, RBNode *nil);