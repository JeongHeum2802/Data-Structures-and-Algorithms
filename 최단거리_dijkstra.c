#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct AdjNode {
	int oppsite;
	int w;
	struct AdjNode* next;
} AdjNode;

typedef struct Vertex {
	AdjNode* AdjList;
} Vertex;

typedef struct HeapNode {
	int d;
	int vertex;
} HeapNode;

typedef struct Heap {
	HeapNode* arr;
	int* pos;
	int n;
} Heap;

// 그래프
AdjNode* getAdjNode();
void addEdge(Vertex* g, int u, int v, int w);
void addAdjNode(AdjNode* header, int u, int w);

// dijkstra
void dijkstra(Vertex *g, int n, int* d);

// Heap
void initHeap(Heap* heap, int n);
void insertItem(Heap* heap, HeapNode node);
HeapNode deleteItem(Heap* heap);
void upHeap(Heap* heap, int idx);
void downHeap(Heap* heap, int idx);
void swapHeapEle(Heap* heap, int a, int b);
void replaceKey(Heap* heap, int vertex, int d);

int main() {
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);
	
	// 그래프 초기화
	Vertex* g = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
	for (int i = 0; i <= n; i++)
		g[i].AdjList = getAdjNode();

	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		addEdge(g, u, v, w);
	}

	// 다익스트라
	int* d = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 0; i <= n; i++) d[i] = 999999999;
	d[s] = 0;

	dijkstra(g, n, d);

	for (int i = 1; i <= n; i++) {
		if (i == s || d[i] == 999999999) continue;
		printf("%d %d\n", i, d[i]);
	}

	// 할당 해제
	for (int i = 0; i <= n; i++) {
		AdjNode* p = g[i].AdjList;
		AdjNode* q;
		while (p != NULL) {
			q = p->next;
			free(p);
			p = q;
		}
	}
	free(g);
	free(d);

	return 0;
}

// 그래프
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
void addAdjNode(AdjNode* header, int u, int w) {
	AdjNode* newNode = getAdjNode();
	newNode->oppsite = u;
	newNode->w = w;
	newNode->next = header->next;
	header->next = newNode;
}

// dijkstra
void dijkstra(Vertex* g, int n, int* d) {
	
	// 우선순위 큐
	Heap heap;
	initHeap(&heap, n);

	for (int i = 1; i <= n; i++) {
		HeapNode temp;
		temp.d = d[i];
		temp.vertex = i;
		insertItem(&heap, temp);
	}

	// 꺼내며 d 테이블 갱신
	int* visited = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 0; i <= n; i++) visited[i] = 0;
	while (heap.n > 0) {
		HeapNode u = deleteItem(&heap);
		d[u.vertex] = u.d;
		visited[u.vertex] = 1;

		AdjNode* p = g[u.vertex].AdjList->next;
		while (p != NULL) {
			if (visited[p->oppsite] == 0 && d[p->oppsite] > d[u.vertex] + p->w) {
				d[p->oppsite] = d[u.vertex] + p->w;
				replaceKey(&heap, p->oppsite, d[u.vertex] + p->w);
			}
			p = p->next;
		}
	}

	// 할당 해제
	free(heap.arr);
	free(heap.pos);
	free(visited);
}

// Heap
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
	swapHeapEle(heap, 1, heap->n);
	heap->n--;
	downHeap(heap, 1);

	return heap->arr[heap->n + 1];
}
void upHeap(Heap* heap, int idx) {
	int parent = idx / 2;
	while (parent >= 1) {
		if (heap->arr[parent].d > heap->arr[idx].d) {
			swapHeapEle(heap, parent, idx);
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
		
		if (heap->arr[smaller].d < heap->arr[idx].d) {
			swapHeapEle(heap, smaller, idx);
			idx = smaller;
			left = idx * 2;
			right = idx * 2 + 1;
		}
		else {
			break;
		}
	}
}
void swapHeapEle(Heap* heap, int a, int b) {
	HeapNode temp = heap->arr[a];
	heap->arr[a] = heap->arr[b];
	heap->arr[b] = temp;

	heap->pos[heap->arr[a].vertex] = a;
	heap->pos[heap->arr[b].vertex] = b;
}
void replaceKey(Heap* heap, int vertex, int d) {
	heap->arr[heap->pos[vertex]].d = d;
	upHeap(heap, heap->pos[vertex]);
}
