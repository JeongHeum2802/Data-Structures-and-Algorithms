#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node* next;
	struct Node* prev;
	int ele;
} Node;

typedef struct Partition {
	struct Node* LT;
	struct Node* EQ;
	struct Node* GT;
} Partition;

Node* getNode();

Node* quickSort(Node* l);
Partition partition(Node* l, int pivot);
Node* merge(Node* LT, Node* EQ, Node* GT);

int main() {
	int n;
	scanf("%d", &n);

	// 연결리스트 입력받아 구축
	Node* l = getNode();
	Node* p = l;
	for (int i = 0; i < n; i++) {
		int ele;
		scanf("%d", &ele);
		Node* newNode = getNode();
		newNode->ele = ele;
		p->next = newNode;
		newNode->prev = p;
		p = p->next;
	}

	p = l;
	l = l->next;
	l->prev = NULL;
	free(p);

	// sort
	l = quickSort(l);

	// 출력
	p = l;
	while (p != NULL) {
		printf(" %d", p->ele);
		p = p->next;
	}
	printf("\n");


	// free
	Node* q;
	p = l;
	while (p != NULL) {
		q = p->next;
		free(p);
		p = q;
	}

	return 0;
}  

// 원소가 ele인 노드를 반환
Node* getNode() {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->ele = 0;
	return newNode;
}

// quickSort
Node* quickSort(Node* l) {
	if (l == NULL || l->next == NULL) // 원소 개수가 하나인 경우
		return l;

	int pivot = l->ele;
	Partition p = partition(l, pivot);
	p.LT = quickSort(p.LT);
	p.GT = quickSort(p.GT);

	return merge(p.LT, p.EQ, p.GT);
}

// LT, EQ, GT로 파티션 분리
Partition partition(Node* l, int pivot) {
	Node* p = l;
	Node* LT = getNode();
	Node* GT = getNode();
	Node* EQ = getNode();

	Node* LTp = LT;
	Node* GTp = GT;
	Node* EQp = EQ;

	while (p != NULL) {
		if (p->ele < pivot) {
			LTp->next = p;
			p = p->next;
			LTp->next->prev = LTp;
			LTp = LTp->next;
			LTp->next = NULL;
		}
		else if (p->ele > pivot) {
			GTp->next = p;
			p = p->next;
			GTp->next->prev = GTp;
			GTp = GTp->next;
			GTp->next = NULL;
		}
		else {
			EQp->next = p;
			p = p->next;
			EQp->next->prev = EQp;
			EQp = EQp->next;
			EQp->next = NULL;
		}
		if (p != NULL)
			p->prev = NULL;
	}

	LTp = LT;
	EQp = EQ;
	GTp = GT;

	LT = LT->next; if (LT) LT->prev = NULL;
	EQ = EQ->next; if (EQ) EQ->prev = NULL;
	GT = GT->next; if (GT) GT->prev = NULL;

	free(LTp);
	free(EQp);
	free(GTp);

	Partition part;
	part.EQ = EQ;
	part.GT = GT;
	part.LT = LT;
	return part;
}

// LT, EQ, GT를 합쳐서 반환
Node* merge(Node *LT, Node *EQ, Node *GT) {
	Node* p;
	// LT가 존재하면
	if (LT) {
		p = LT;

		while (p->next != NULL)
			p = p->next;
		
		p->next = EQ;
		EQ->prev = p;

		while (p->next != NULL)
			p = p->next;

		if (GT) {
			p->next = GT;
			GT->prev = p;
		}

		return LT;
	}
	else {
		p = EQ;
		
		while (p->next != NULL)
			p = p->next;

		if (GT) {
			p->next = GT;
			GT->prev = p;
		}

		return EQ;
	}
}
