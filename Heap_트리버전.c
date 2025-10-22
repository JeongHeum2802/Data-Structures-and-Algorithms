#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	int key;
} Node;

Node* getNode(); // 비어있는 노드 반환
int isExternal(Node* v); // 외부 노드인지 확인
Node* advanceLast(Node* v); // last노드 전진
Node* retreatLast(Node* v); // last노드 후퇴
void insertItem(Node** root, Node** lastNode, int key); // 아이텀 추가
int deleteItem(Node** root, Node** lastNode); // 아이템 제거 후 반환
void expandExternal(Node* v); // 외부노드 확장
void reduceExternal(Node** root, Node* v); // 노드 제거 후 외부노드 축소
void upHeap(Node* v); // upHeap
void downHeap(Node* v); // downHeap

void printHeap(Node* root);
void freeHeap(Node* root);

int main() {
	Node* root = getNode();
	Node* lastNode = NULL;

	char cmd;
	scanf("%c", &cmd);
	while (cmd != 'q') {
		if (cmd == 'i') {
			int key;
			scanf("%d", &key);
			insertItem(&root, &lastNode, key);
		} 
		else if (cmd == 'd') {
			int key = deleteItem(&root, &lastNode);
			printf("%d\n", key);
		}
		else if (cmd == 'p') {
			printHeap(root);
			printf("\n");
		}

		scanf(" %c", &cmd);
	}

	freeHeap(root);
	return 0;
}


void printHeap(Node* root) {
	if (isExternal(root)) return;
	printf("%d ", root->key);
	printHeap(root->left);
	printHeap(root->right);
}
void freeHeap(Node* root) {
	if (root == NULL) return;
	freeHeap(root->left);
	freeHeap(root->right);

	free(root);
}

// 노드 반환
Node* getNode() {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	newNode->key = -1;
	return newNode;
}

// 외부 노드면 1 아니면 0 리턴
int isExternal(Node* v) {
	return (v->left == NULL && v->right == NULL);
}

// lastNode를 다음 위치로 옮김
Node* advanceLast(Node* v) {

	// 자신이 오른쪽 자식인 동안 부모로
	Node* p = v->parent;
	while (p != NULL && p->right == v) {
		v = p;
		p = v->parent;
	}

	// 자신이 왼쪽 자식이면 형제로
	if (p != NULL && p->left == v)
		v = p->right;

	while (!isExternal(v))
		v = v->left;

	return v;
}

// lastNode를 전 위치로 옮김 (원소가 없으면 NULL 리턴)
Node* retreatLast(Node* v) {
	
	// 자신이 왼쪽 자식인 경우 부모로
	Node* p = v->parent;
	while (p != NULL && p->left == v) {
		v = p;
		p = v->parent;
	}

	if (p != NULL && p->right == v)
		v = p->left;

	while (!isExternal(v))
		v = v->right;

	return v->parent;
}

// 힙에 아이템 삽입
void insertItem(Node** root, Node** lastNode, int key) {

	// 아이템이 없으면 루트 변경
	if (isExternal(*root)) {
		*lastNode = *root;
	}
	else {
		*lastNode = advanceLast(*lastNode);
	}

	(*lastNode)->key = key;
	expandExternal(*lastNode);
	upHeap(*lastNode);
	return;
}

// 힙에서 아이템을 제거하고 값을 반환
int deleteItem(Node** root, Node** lastNode) {
	if (isExternal(*root)) return -404;

	int key = (*root)->key;

	(*root)->key = (*lastNode)->key; // 루트에 마지막 노드 값 대입

	Node* v = *lastNode;
	Node* retreatNode = retreatLast(*lastNode);
	if (*lastNode == retreatNode) { // 원소가 하나 남았을 때 lastNode 를 NULL
		*lastNode = NULL;
	}
	else {
		*lastNode = retreatNode;
	}

	Node* z = v->left;
	reduceExternal(root, z);
	downHeap(*root);

	return key;
}

// 노드에 외부노드 연장
void expandExternal(Node* v) {
	Node* left = getNode();
	Node* right = getNode();
	left->parent = v;
	right->parent = v;
	v->left = left;
	v->right = right;
	return;
}

// 노드 축소
void reduceExternal(Node** root, Node* z) {
	Node* y = z->parent;
	Node* g = y->parent;
	Node* zs = (y->left == z) ? y->right : y->left;

	zs->parent = g;
	if (zs->parent == NULL) *root = zs;
	else {
		if (g->left == y) g->left = zs;
		else g->right = zs;
	}

	free(y);
	free(z);
}

// upHeap
void upHeap(Node* v) {
	// 루트, 값이 부모보다 크거나 같으면 return
	if (v->parent == NULL || v->key >= v->parent->key) return;

	// upHeap
	int temp = v->key;
	v->key = v->parent->key;
	v->parent->key = temp;
	upHeap(v->parent);

	return;
}

// downHeap
void downHeap(Node* v) {
	if (isExternal(v) || isExternal(v->left)) return; // 원소가 한개일 때 외부노드v로 접근됨

	Node* smaller = v->left;
	if (!isExternal(v->right) && smaller->key > v->right->key) {
		smaller = v->right;
	}

	if (v->key <= smaller->key) return;
	int temp = v->key;
	v->key = smaller->key;
	smaller->key = temp;

	downHeap(smaller);
}
