#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node* next;
	struct Node* prev;
	int ele;
} Node;

typedef struct Partition {
	struct Node* l1;
	struct Node* l2;
} Partition;

Node* getNode(); // 빈 노드 반환
Node* mergeSort(Node* l, int n); // mergeSort
Node* merge(Node* l1, Node* l2); // 두 리스트를 정렬하며 합병
Partition partition(Node* l, int n); // 리스트를 두개의 리스트로 쪼갬


int main() {
	Node* l = NULL;
	int n;

	scanf("%d", &n);

	Node* p = NULL;
	// list 입력 받기
	for (int i = 0; i < n; i++) {
		int ele;
		scanf("%d", &ele);

		if (i == 0) { // 첫 노드는 따로 처리
			l = getNode();
			l->ele = ele;
			p = l;
		}
		else {
			p->next = getNode();
			p->next->prev = p;
			p = p->next;
			p->ele = ele;
		}
	}

	// 합병정렬
	l = mergeSort(l, n);

	// 리스트 출력
	p = l;
	while (p != NULL) {
		printf(" %d", p->ele);
		p = p->next;
	}

	Node* q = NULL;
	p = l;
	while (p != NULL) {
		q = p->next;
		free(p);
		p = q;
	}
	return 0;
}

// 빈 노드를 반환
Node* getNode() {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->ele = 0;
	return newNode;
}

// mergeSort
Node* mergeSort(Node* l, int n) {
	if (n > 1) {
		// 분할
		Partition p = partition(l, n / 2);

		// 재귀
		p.l1 = mergeSort(p.l1, n / 2);
		p.l2 = mergeSort(p.l2, n - (n / 2));

		// 통치
		return merge(p.l1, p.l2);
	}

	// 본인 바로 리턴
	return l;
}

// 두 리스트를 절반으로 쪼개 반환
Partition partition(Node* l, int n) {
	Node* l1;
	Node* l2;
	l1 = l;

	// q를 l1 끝 노드로 이동 
	Node* q = l;
	for (int i = 0; i < n - 1; i++)
		q = q->next;

	// l2 연결 조정
	l2 = q->next;
	q->next = NULL;
	l2->prev = NULL;

	Partition p;
	p.l1 = l1;
	p.l2 = l2;
	return p;
}

// 두 리스트를 정렬하고 반환
Node* merge(Node* l1, Node* l2) {
	Node* newList = NULL;
	
	// 첫 값 대입
	if (l1->ele < l2->ele) {
		newList = l1;
		l1 = l1->next;
	}
	else {
		newList = l2;
		l2 = l2->next;
	}

	Node* p = newList;
	while (l1 != NULL && l2 != NULL) {
		if (l1->ele < l2->ele) {
			p->next = l1;
			l1->prev = p;
			l1 = l1->next;
			p = p->next;
		} 
		else {
			p->next = l2;
			l2->prev = p;
			l2 = l2->next;
			p = p->next;
		}
	}

	if (l1 != NULL) {
		p->next = l1;
		l1->prev = p;
	}

	if (l2 != NULL) {
		p->next = l2;
		l2->prev = p;
	}

	return newList;
}
