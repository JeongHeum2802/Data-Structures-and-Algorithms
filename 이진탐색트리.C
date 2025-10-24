#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	int key;
} Node;

Node* getNode();
int isExternal(Node* v);
void expandExternal(Node* v);
void reduceExternal(Node** root, Node* z);
Node* inordercc(Node* v);

void printTree(Node* v);
void freeTree(Node* v) {
	if (v == NULL) return;
	
	freeTree(v->left);
	freeTree(v->right);
	free(v);
}

Node* treeSearch(Node* v, int key);
void insertItem(Node** root, int key);
int deleteItem(Node** root, int key);

int main() {
	Node* root = getNode();

	char cmd;
	scanf("%c", &cmd);
	while (cmd != 'q') {
		if (cmd == 'i') {
			int key;
			scanf("%d", &key);
			insertItem(&root, key);
		}
		else if (cmd == 'd') {
			int key;
			scanf("%d", &key);
			int re = deleteItem(&root, key);
			printf("%d\n", re);
		}
		else if (cmd == 'p') {
			printTree(root);
			printf("\n");
		}

		scanf(" %c", &cmd);
	}

	freeTree(root);
	return 0;
}

Node* getNode() {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	newNode->key = 0;
	return newNode;
}
void printTree(Node* v) {
	if (isExternal(v)) return;
	printf(" %d", v->key);
	printTree(v->left);
	printTree(v->right);
}

int isExternal(Node* v) {
	return (v->left == NULL && v->right == NULL);
}
void expandExternal(Node* v) {
	Node* left = getNode();
	Node* right = getNode();
	v->left = left;
	v->right = right;
	left->parent = v;
	right->parent = v;
}
void reduceExternal(Node** root, Node* z) {
	Node* w = z->parent; // 부모
	Node* g = w->parent; // 조상
	Node* zs = (w->left == z) ? w->right : w->left; // 형제
	
	if (g == NULL) {
		*root = zs;
	}
	else {
		if (g->left == w)
			g->left = zs;
		else
			g->right = zs;		
	}

	zs->parent = g;
	free(z);
	free(w);
}
Node* inordercc(Node* v) {
	Node* y = v->right;
	while (!isExternal(y))
		y = y->left;
	y = y->parent;
	return y;
}

Node* treeSearch(Node* v, int key) {
	if (isExternal(v)) return v;

	if (v->key == key)
		return v;
	else if (key < v->key)
		return treeSearch(v->left, key);
	else
		return treeSearch(v->right, key);
}

void insertItem(Node** root, int key) {
	Node* w = treeSearch(*root, key);
	if (!isExternal(w)) return;
	
	w->key = key;
	expandExternal(w);
}
int deleteItem(Node** root, int key) {
	Node* w = treeSearch(*root, key);
	if (isExternal(w)) return;

	int ele = w->key;
	Node* z = w->left;

	if (!isExternal(z))
		z = w->right;
	if (isExternal(z)) {
		reduceExternal(root, z);
	}
	else {
		Node* y = inordercc(w);
		w->key = y->key;
		reduceExternal(root, y->left);
	}
	return ele;
}
