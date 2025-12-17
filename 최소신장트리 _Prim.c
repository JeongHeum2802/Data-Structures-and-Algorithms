#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct HeapNode {
	int d;
	int vertex;
} HeapNode;

typedef struct Heap {
	HeapNode* arr;
	int* pos; // pos[2] = 3 -> 2번노드가 우선순위 큐에서 3번재 첨자에 있음
	int n;
} Heap;

typedef struct AdjNode {
	int oppsite;
	int w;
	struct AdjNode* next;
} AdjNode;

typedef struct Vertex {
	AdjNode* AdjList;
} Vertex;

// graph
AdjNode* getAdjNode();
void addEdge(Vertex* g, int u, int v, int w);
void addAdjNode(AdjNode* header, int v, int w);

// heap (key = d) 최소힙
void initHeap(Heap* heap, int n);
void insertItem(Heap *heap, HeapNode node);
HeapNode deleteItem(Heap* heap);
void upHeap(Heap* heap, int idx);
void downHeap(Heap* heap, int idx);
void swap(Heap* heap, int a, int b);
void setkey(Heap* heap, int idx, int d);

void prim(Heap* heap, Vertex* g, int *d);

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	// 그래프 초기화
	Vertex* g = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
	for (int i = 0; i <= n; i++) 
		g[i].AdjList = getAdjNode();
	
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		addEdge(g, u, v, w);
	}

	// 우선순위 큐
	Heap heap;
	initHeap(&heap, n);

	// d테이블
	int* d = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 0; i <= n; i++)
		d[i] = 999999999;
	d[1] = 0;

	for (int i = 1; i <= n; i++) {
		HeapNode temp;
		temp.d = d[i];
		temp.vertex = i;
		insertItem(&heap, temp);
	}

	// prim
	prim(&heap, g, d);

	int sum = 0;
	for (int i = 1; i <= n; i++)
		sum += d[i];

	printf("\n%d", sum);

	// 할당 해제
	free(d);
	free(heap.arr);
	free(heap.pos);
	for (int i = 0; i <= n; i++) {
		AdjNode *p = g[i].AdjList;
		AdjNode* q;
		while (p != NULL) {
			q = p->next;
			free(p);
			p = q;
		}
	}
	free(g);

	return 0;
}

AdjNode* getAdjNode() {
	AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
	newNode->oppsite = -1;
	newNode->w = -1;
	newNode->next = NULL;
	return newNode;
}
void addEdge(Vertex* g, int u, int v, int w) {
	addAdjNode(g[u].AdjList, v, w);
	addAdjNode(g[v].AdjList, u, w);
}
void addAdjNode(AdjNode* header, int v, int w) {
	AdjNode* newNode = getAdjNode();
	newNode->oppsite = v;
	newNode->w = w;
	newNode->next = header->next;
	header->next = newNode;
}


// heap (key = d) 최소힙
void initHeap(Heap* heap, int n) {
	heap->arr = (HeapNode*)malloc(sizeof(HeapNode) * (n + 1));
	heap->pos = (int*)malloc(sizeof(int) * (n + 1));
	heap->n = 0;
}
void insertItem(Heap* heap, HeapNode node) {
	heap->n++;
	heap->arr[heap->n] = node;
	heap->pos[node.vertex] = heap->n;
	upHeap(heap, heap->n);
}
HeapNode deleteItem(Heap* heap) {
	swap(heap, 1, heap->n);
	HeapNode temp = heap->arr[heap->n];
	heap->n--;
	downHeap(heap, 1);
	return temp;
}
void upHeap(Heap* heap, int idx) {
	int parent = idx / 2;
	while (parent >= 1) {
		if (heap->arr[idx].d < heap->arr[parent].d) {
			swap(heap, idx, parent);
			idx = parent;
			parent /= 2;
		}
		else {
			break;
		}
	}
}
void downHeap(Heap* heap, int idx) {
	int left = idx * 2;
	int right = idx * 2 + 1;
	while (left <= heap->n) {
		int smaller = left;
		if (right <= heap->n && heap->arr[smaller].d > heap->arr[right].d) 
			smaller = right;
		
		if (heap->arr[idx].d > heap->arr[smaller].d) {
			swap(heap, idx, smaller);
			idx = smaller;
			left = idx * 2;
			right = idx * 2 + 1;
		}
		else {
			break;
		}
	}
}
void swap(Heap* heap, int a, int b) {
	HeapNode temp = heap->arr[a];
	heap->arr[a] = heap->arr[b];
	heap->arr[b] = temp;

	// pos 갱신 ( 현재 heap[a]에 있는 원소의 포지션은 a이다 )
	heap->pos[heap->arr[a].vertex] = a;
	heap->pos[heap->arr[b].vertex] = b;
}
void setkey(Heap* heap, int vertex, int d) {
	heap->arr[heap->pos[vertex]].d = d;
	upHeap(heap, heap->pos[vertex]);
}

void prim(Heap* heap, Vertex* g, int* d) {
	int* visited = (int*)malloc(sizeof(int) * (heap->n + 1));
	for (int i = 0; i <= heap->n; i++) visited[i] = 0;

	while (heap->n > 0) {
		HeapNode temp = deleteItem(heap);
		visited[temp.vertex] = 1;
		printf(" %d", temp.vertex);
		// 인접 노드 검사
		AdjNode* p = g[temp.vertex].AdjList->next;
		while (p != NULL) {
			if (visited[p->oppsite] == 0 && p->w < d[p->oppsite]) {
				d[p->oppsite] = p->w;
				setkey(heap, p->oppsite, p->w);
			}
			p = p->next;
		}
	}
	free(visited);
}
