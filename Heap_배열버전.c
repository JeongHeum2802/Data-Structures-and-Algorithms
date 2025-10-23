#include <stdio.h>
#include <stdlib.h>

void insertItem(int* heap, int* n, int key); // 아이템 추가
void upHeap(int* heap, int* n); // upHeap
int deleteItem(int* heap, int* n); // 아이템 제거 후 반환
void downHeap(int* heap, int* n, int v); // downHeap
void printHeap(int* heap, int n);

int main() {
	int heap[101];
	int n = 0;

	char cmd;
	scanf("%c", &cmd);
	while (cmd != 'q') {
		if (cmd == 'i') {
			int key;
			scanf("%d", &key);
			insertItem(heap, &n, key);
		}
		else if (cmd == 'd') {
			int key = deleteItem(heap, &n);
			printf("%d\n", key);
		}
		else if (cmd == 'p') {
			printHeap(heap, n);
		}
		scanf(" %c", &cmd);
	}
	
	return 0;
}

void printHeap(int* heap, int n) {
	for (int i = 1; i <= n; i++)
		printf(" %d", heap[i]);
	printf("\n");
}

// 아이템 추가
void insertItem(int* heap, int* n, int k) {
	if (*n >= 100) return;
	(*n)++;
	heap[*n] = k;
	upHeap(heap, n);
}

// upHeap(while)
void upHeap(int* heap, int* n) {
	int v = *n;
	int parent = v / 2;
	while (parent >= 1 && heap[parent] > heap[v]) {
		int temp = heap[parent];
		heap[parent] = heap[v];
		heap[v] = temp;
		v = parent;
		parent = v / 2;
	}
}

// 아이템 제거 후 반환
int deleteItem(int* heap, int* n) {
	if (*n == 0) return -404;
	int key = heap[1];
	heap[1] = heap[*n];
	(*n)--;

	downHeap(heap, n, 1);
	return key;
}

void downHeap(int* heap, int* n, int v) {
	while (v * 2 <= *n) {
		int left = v * 2;
		int right = v * 2 + 1;

		int smaller = left;
		if (right <= *n && heap[smaller] > heap[right])
			smaller = right;

		if (heap[v] <= heap[smaller]) break;

		int temp = heap[v];
		heap[v] = heap[smaller];
		heap[smaller] = temp;

		v = smaller;
	}
}

