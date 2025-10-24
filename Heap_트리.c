#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node* parent;
	struct Node* left;
	struct Node* right;
	int k;
} Node;

// util
Node* getNode();
int isExternal(Node* v);
void swapEle(Node* a, Node* b);
void printHeap(Node* root);
void freeHeap(Node* v);

// LastNode
Node* advanceLast(Node* root, Node* last);
Node* retreatLast(Node* root, Node* last);

// insert
void insertItem(Node* root, Node** lastNode, int k);
void expandExternal(Node* v);
void upHeap(Node* v);

// remove
int removeItem(Node** root, Node** lastNode);
void reduceExternal(Node** root, Node* v);
void downHeap(Node* v);


int main() {
	Node* root = getNode();
	Node* lastNode = NULL;

	insertItem(root, &lastNode, 3);
	insertItem(root, &lastNode, 6);
	insertItem(root, &lastNode, 2);
	insertItem(root, &lastNode, 9);

	printHeap(root);
	printf("\n");

	printf("%d\n", removeItem(&root, &lastNode));
	printf("%d\n", removeItem(&root, &lastNode));
	printf("%d\n", removeItem(&root, &lastNode));
	printf("%d\n", removeItem(&root, &lastNode));

	freeHeap(root);
	return 0;
}

//// util
Node* getNode() {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	newNode->k = -1;
	return newNode;
}
int isExternal(Node* v) {
	return v->left == NULL && v->right == NULL;
}
void swapEle(Node* a, Node* b) {
	int temp = a->k;
	a->k = b->k;
	b->k = temp;
}
void printHeap(Node* root) {
	if (isExternal(root)) return;
	printf(" %d", root->k);
	printHeap(root->left);
	printHeap(root->right);
}
void freeHeap(Node* v) {
	if (v == NULL) return;
	freeHeap(v->left);
	freeHeap(v->right);
	free(v);
}

//// LastNode

// 새로 삽입될 노드를 반환
Node* advanceLast(Node* root, Node* last) {
	if (isExternal(root)) // 힙이 비어있으면 루트노드 반환
		return root;

	Node* v = last;

	// 루트가 아니고 부모의 오른쪽에 위치할 때
	while (v->parent && v->parent->right == v) 
		v = v->parent;

	if (v->parent && v->parent->left == v) // 형제로 이동
		v = v->parent->right;

	// 왼쪽 외부노드로 이동
	while (!isExternal(v))
		v = v->left;

	return v;
}
// 후퇴될 노드를 반환
Node* retreatLast(Node* root, Node* last) {
	if (last == root) // 원소가 하나인 경우
		return NULL;

	Node* v = last;
	
	// 자신이 부모의 왼쪽 자식일 때
	while (v->parent && v->parent->left == v)
		v = v->parent;

	// 형제로 가기
	if (v->parent && v->parent->right == v)
		v = v->parent->left;

	while (!isExternal(v->right))
		v = v->right;

	return v;
}

//// insert
void insertItem(Node* root, Node** lastNode, int k) {
	*lastNode = advanceLast(root, *lastNode);
	(*lastNode)->k = k;
	expandExternal(*lastNode);
	upHeap(*lastNode);
}
void expandExternal(Node* v) {
	Node* left = getNode();
	Node* right = getNode();
	left->parent = v;
	right->parent = v;

	v->left = left;
	v->right = right;
}
void upHeap(Node* v) {
	if (v->parent == NULL) return;

	if (v->parent->k <= v->k) return;

	swapEle(v->parent, v);
	upHeap(v->parent);
}

//// remove
int removeItem(Node** root, Node** lastNode) {
	int ele = (*root)->k;
	swapEle(*root, *lastNode);

	// lastNode 후퇴 후 축소
	Node* z = *lastNode;
	*lastNode = retreatLast(*root, *lastNode);
	reduceExternal(root, z->left);

	// downHeap
	downHeap(*root);
	return ele;
}
void reduceExternal(Node** root, Node* v) {
	Node* w = v->parent; // 부모
	Node* g = w->parent; // 조상
	Node* zs = (w->left == v) ? w->right : w->left; // 형제

	if (g == NULL) { // 조상이 없음 (원래 w가 루트)
		*root = zs;
		zs->parent = NULL;
	}
	else {
		if (g->right == w)
			g->right = zs;
		else
			g->left = zs;
		zs->parent = g;
	}

	free(v);
	free(w);
}
void downHeap(Node* v) {
	if (isExternal(v)) return;
	Node* left = v->left;
	Node* right = v->right;

	Node* smaller = NULL;
	if (!isExternal(left))
		smaller = left;
	if (!isExternal(right) && right->k < smaller->k)
		smaller = right;

	if (smaller == NULL || v->k <= smaller->k) return;

	swapEle(v, smaller);
	downHeap(smaller);
}
