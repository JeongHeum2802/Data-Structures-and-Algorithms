#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
	int u;
	int v;
	int w;
} Edge;

// 우선순위 큐
typedef struct Heap {
	Edge* arr;
	int n;
} Heap;

void initHeap(Heap* heap, int n); // Heap 초기화
void insertItem(Heap* heap, Edge edge);
Edge deleteItem(Heap* heap);
void upHeap(Heap* heap, int idx);
void downHeap(Heap* heap, int idx);
void swapHeapItem(Heap* heap, int idx1, int idx2);

// 분리집합
int find(int* parent, int u);
void Union(int* parent, int u, int v);

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	Edge* edges = (Edge*)malloc(sizeof(Edge) * m);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges[i].u = u;
		edges[i].v = v;
		edges[i].w = w;
	}

	// 우선순위 큐
	Heap heap;
	initHeap(&heap, m);
	for (int i = 0; i < m; i++)
		insertItem(&heap, edges[i]);

	// 분리집합
	int* parent = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 0; i <= n; i++)
		parent[i] = i;


	Edge* Mst = (Edge*)malloc(sizeof(Edge) * n);
	int i = 0;
	while (heap.n > 0 && i < n - 1) {
		Edge e = deleteItem(&heap);
		if (find(parent, e.u) != find(parent, e.v)) {
			Mst[i] = e;
			Union(parent, e.u, e.v);
			i++;
		}
	}

	int sum = 0;
	for (int i = 0; i < n - 1; i++) {
		printf(" %d", Mst[i].w);
		sum += Mst[i].w;
	}

	printf("\n%d", sum);

	// 할당해제
	free(edges);
	free(parent);
	free(heap.arr);
	free(Mst);

	return 0;
}

void initHeap(Heap* heap, int n) {
	heap->arr = (Edge*)malloc(sizeof(Edge) * (n + 1));
	heap->n = 0;
}
void insertItem(Heap* heap, Edge edge) {
	heap->n++;
	heap->arr[heap->n] = edge;
	upHeap(heap, heap->n);
}
Edge deleteItem(Heap* heap) {
	swapHeapItem(heap, 1, heap->n);
	heap->n--;
	downHeap(heap, 1);
	return heap->arr[heap->n + 1];
}
void upHeap(Heap* heap, int idx) {
	int parent = idx / 2;
	while (parent >= 1) {
		if (heap->arr[parent].w > heap->arr[idx].w) {
			swapHeapItem(heap, idx, parent);
			
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
		if (right <= heap->n && heap->arr[right].w < heap->arr[smaller].w)
			smaller = right;

		if (heap->arr[smaller].w < heap->arr[idx].w) {
			swapHeapItem(heap, smaller, idx);
			idx = smaller;
			left = idx * 2;
			right = idx * 2 + 1;
		}
		else {
			break;
		}
	}
}
void swapHeapItem(Heap* heap, int idx1, int idx2) {
	Edge temp = heap->arr[idx1];
	heap->arr[idx1] = heap->arr[idx2];
	heap->arr[idx2] = temp;
}

int find(int* parent, int u) {
	if (parent[u] != u) {
		parent[u] = find(parent, parent[u]);
	}
	return parent[u];
}
void Union(int* parent, int u, int v) {
	int pu = find(parent, u);
	int pv = find(parent, v);
	if (pu == pv)
		return;

	if (pu < pv)
		parent[pv] = pu;
	else
		parent[pu] = pv;
}
