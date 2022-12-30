#include "red_black_tree.h"
#include <iostream>
using namespace std;

RBNode* createNode(int key, bool color, RBNode *nil) {
	RBNode *nd = new RBNode;
	nd->key = key;
	nd->color = color;
	nd->left = nd->right = nd->parent = nil;
	return nd;
}

void leftRotate(RBNode *&root, RBNode *x, RBNode *nil) {
	RBNode *y = x->right;
	x->right = y->left;
	if (y->left != nil)
		y->left->parent = x;
	y->parent = x->parent;

	if (x->parent == nil)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void rightRotate(RBNode *&root, RBNode *y, RBNode *nil) {
	RBNode *x = y->left;
	y->left = x->right;
	if (x->right != nil)
		x->right->parent = y;
	x->parent = y->parent;

	if (y->parent == nil)
		root = x;
	else if (y == y->parent->right)
		y->parent->right = x;
	else
		y->parent->left = x;
	x->right = y;
	y->parent = x;
}

void insertBST(RBNode *&root, RBNode *x, RBNode *nil) {
	RBNode *y = nil;
	RBNode *z = root;
	while (z != nil) {
		y = z;
		if (x->key < z->key) z = z->left;
		else z = z->right;
	}
	x->parent = y;
	if (y == nil) root = x;
	else if (x->key < y->key) y->left = x;
	else y->right = x;
}

void insertAdjustLeft(RBNode *&root, RBNode *&x, RBNode *nil) {
	RBNode *u = x->parent->parent->right;
	if (u->color == RED) {
		x->parent->color = BLACK;
		u->color = BLACK;
		x->parent->parent->color = RED;
		x = x->parent->parent;
	}
	else {
		if (x == x->parent->right) {
			x = x->parent;
			leftRotate(root, x, nil);
		}
		x->parent->color = BLACK;
		x->parent->parent->color = RED;
		rightRotate(root, x->parent->parent, nil);
	}
}

void insertAdjustRight(RBNode *&root, RBNode *&x, RBNode *nil) {
	RBNode *u = x->parent->parent->left;
	if (u->color == RED) {
		x->parent->color = BLACK;
		u->color = BLACK;
		x->parent->parent->color = RED;
		x = x->parent->parent;
	}
	else {
		if (x == x->parent->left) {
			x = x->parent;
			rightRotate(root, x, nil);
		}
		x->parent->color = BLACK;
		x->parent->parent->color = RED;
		leftRotate(root, x->parent->parent, nil);
	}
}

void insertAdjust(RBNode *&root, RBNode *x, RBNode *nil) {
	while (x->parent->color == RED)
		if (x->parent == x->parent->parent->left)
			insertAdjustLeft(root, x, nil);
		else
			insertAdjustRight(root, x, nil);
	root->color = BLACK;
}

RBNode* succesor(RBNode *x, RBNode *nil) {
	if (x->right != nil) {
		RBNode *ptr = x->right;
		while (ptr->left != nil) {
			ptr = ptr->left;
		}
		return ptr;
	}
	RBNode *ptr = x->parent;
	while (ptr != nil && x == ptr->right) {
		x = ptr;
		ptr = ptr->parent;
	}
	return ptr;
}

void removeAdjustLeft(RBNode *&root, RBNode *&x, RBNode *nil) {
	RBNode *w = x->parent->right;
	if (w->color == RED) {
		w->color = BLACK;
		x->parent->color = RED;
		leftRotate(root, x->parent, nil);
		w = x->parent->right;
	}
	if (w->right->color == BLACK && w->left->color == BLACK) {
		w->color = RED;
		x = x->parent;
	}
	else {
		if (w->right->color == BLACK) {
			w->left->color = BLACK;
			w->color = RED;
			rightRotate(root, w, nil);
			w = x->parent->right;
		}
		w->color = x->parent->color;
		x->parent->color = BLACK;
		w->right->color = BLACK;
		leftRotate(root, x->parent, nil);
		x = root;
	}
}

void removeAdjustRight(RBNode *&root, RBNode *&x, RBNode *nil) {
	RBNode *w = x->parent->left;
	if (w->color == RED) {
		w->color = BLACK;
		x->parent->color = RED;
		rightRotate(root, x->parent, nil);
		w = x->parent->left;
	}
	if (w->left->color == BLACK && w->right->color == BLACK) {
		w->color = RED;
		x = x->parent;
	}
	else {
		if (w->left->color == BLACK) {
			w->right->color = BLACK;
			w->color = RED;
			leftRotate(root, w, nil);
			w = x->parent->left;
		}
		w->color = x->parent->color;
		x->parent->color = BLACK;
		w->left->color = BLACK;
		rightRotate(root, x->parent, nil);
		x = root;
	}
}

void removeAdjust(RBNode *root, RBNode *x, RBNode *nil) {
	while ((x->color == BLACK) && (x != root))
		if (x == x->parent->left)
			removeAdjustLeft(root, x, nil);
		else
			removeAdjustRight(root, x, nil);
	x->color = BLACK;
}

void printPreOrder(RBNode *root, RBNode *nil) {
	if (root == nil) return;
	cout << root->key << " ";
	printPreOrder(root->left, nil);
	printPreOrder(root->right, nil);
}

void printPostOrder(RBNode *root, RBNode *nil) {
	if (root == nil) return;
	printPostOrder(root->left, nil);
	printPostOrder(root->right, nil);
	cout << root->key << " ";
}

void printInOrder(RBNode *root, RBNode *nil) {
	if (root == nil) return;
	printInOrder(root->left, nil);
	cout << root->key << " ";
	printInOrder(root->right, nil);
}

int max(int a, int b) {
	return a > b ? a : b;
}

int nodeHeight(RBNode *x, RBNode *nil) {
	if (x == nil) return -1;
	return max(nodeHeight(x->left, nil), nodeHeight(x->right, nil)) + 1;
}

void removeSubTree(RBNode *&root, RBNode *nil) {
	if (root == nil) return;
	removeSubTree(root->left, nil);
	removeSubTree(root->right, nil);
	delete root;
	root = nil;
}

void removeTree(RBNode *&root, RBNode *&nil) {
	removeSubTree(root, nil);
	delete nil;
	root = nil = NULL;
}

void Insert(RBNode *&root, int key, RBNode *nil) {
	RBNode *x = createNode(key, RED, nil);
	insertBST(root, x, nil);
	insertAdjust(root, x, nil);
}

RBNode* createTree(int a[], int n, RBNode *&nil) {
	nil = new RBNode;
	nil->color = BLACK;
	nil->parent = nil->left = nil->right = nil;
	RBNode *root = nil;
	for (int i = 0; i < n; i++)
		Insert(root, a[i], nil);
	root->parent = nil;
	return root;
}

RBNode* lookUp(RBNode *root, int key, RBNode *nil) {
	if (root == nil || root->key == key) return root;
	if (key < root->key) return lookUp(root->left, key, nil);
	else return lookUp(root->right, key, nil);
}

//Height starts at 0 at root, only accept tree's root as argument
int Height(RBNode *root) {
	RBNode *nil = root->parent;
	return nodeHeight(root, nil);
}

//Dont count NIL leaf for height, root's height is 1, only accept tree's root as argument
int BlackHeight(RBNode *root) {
	int h = 0;
	RBNode *nil = root->parent;
	RBNode *ptr = root;
	while (ptr != nil) {
		if (ptr->color == BLACK) h++;
		ptr = ptr->left;
	} 
	return h;
}

int Remove(RBNode *root, int key, RBNode *nil) {
	RBNode *z = lookUp(root, key, nil);
	if (z == nil) return 0;
	RBNode *y = z;
	if (z->left != nil && z->right != nil)
		y = succesor(z, nil);
	RBNode *x = (y->left == nil) ? y->right : y->left;
	x->parent = y->parent;
	if (y->parent == nil)
		root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	if (y != z)
		z->key = y->key;
	if (y->color == BLACK)
		removeAdjust(root, x, nil);
	delete y;
	return 1;
}

//This function is for testing purpose and is not required in Homework instruction
// int main() {
// 	int a[] = {30,88,81,6,66,10,97,13,18,79};
// 	int n = sizeof(a) / sizeof(int);
// 	RBNode *nil;
// 	RBNode *root = createTree(a, n, nil);
// 	printPreOrder(root, nil);
// 	cout << endl;
// 	cout << "Height: " << Height(root) << endl;
// 	cout << "BlackHeight: " << BlackHeight(root) << endl;
// 	Remove(root, 79, nil);
// 	Remove(root, 97, nil);
// 	Remove(root, 18, nil);
// 	cout << "Height: " << Height(root) << endl;
// 	cout << "BlackHeight: " << BlackHeight(root) << endl;
// 	printPreOrder(root, nil);
// 	cout << endl;
// 	removeTree(root, nil);
// }