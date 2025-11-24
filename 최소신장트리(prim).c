#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct AdjNode {
	int vertex;
	int weight;
	struct AdjNode* next;
} AdjNode;

typedef struct Vertex {
	int pointer; // 우선순위 큐에서 사용할 인덱스 위치 표시자
	int d;
	int p;
	AdjNode* AdjList;
} Vertex;

AdjNode* getAdjNode(); // AdjNode반환
void initGraph(Vertex* graph, int n); // 그래프 초기화
void insertAdjNode(AdjNode* AdjList, int v, int w); //AdjNode 추가

void insertPQ(Vertex* pq, int* n, int pointer, Vertex v); // PQ에 원소 삽입
void upHeap(Vertex* pq, int* n, int v); // upHeap
Vertex removeMin(Vertex* pq, int* n); // PQ에서 원소 제거
void downHeap(Vertex* pq, int* n, int v); // downHeap
void setKey(Vertex* pq, int* n, int pointer, int w); // pq에서 pointer를 가르키는 원소의 w를 설정

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	// 그래프 선언 후 초기화
	Vertex* graph = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
	initGraph(graph, n);

	// 가중치 입력받아 인접리스트 초기화
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		insertAdjNode(graph[u].AdjList, v, w);
		insertAdjNode(graph[v].AdjList, u, w);
	}

	// 우선순위 큐
	Vertex* pq = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
	int pqN = 0; // 0이면 pq가 비어있음

	// 1번 정점만 d를 0으로, 나머지는 그대로 pq에 넣기
	graph[1].d = 0;
	for (int i = 1; i <= n; i++)
		insertPQ(pq, &pqN, i, graph[i]);

	// pq 값을 빼면서 최소진장트리 찾기
	int* visited = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++)
		visited[i] = 0;

	int sum = 0;
	while (pqN != 0) {
		Vertex pop = removeMin(pq, &pqN);
		visited[pop.pointer] = 1;
		printf(" %d", pop.pointer);
		sum += pop.d;

		AdjNode* p = graph[pop.pointer].AdjList->next;

		while (p != NULL) {
			if (visited[p->vertex] == 0 && graph[p->vertex].d > p->weight) {
				graph[p->vertex].d = p->weight;
				// 우선순위 큐에서의 weight도 설정
				setKey(pq, &pqN, p->vertex, p->weight);
				graph[p->vertex].p = pop.pointer;
			}
			p = p->next;
		}
	}

	printf("\n%d", sum);

	// 할당 해제
	for (int i = 0; i <= n; i++) {
		AdjNode* p = graph[i].AdjList;
		AdjNode* q;
		while (p != NULL) {
			q = p->next;
			free(p);
			p = q;
		}
	}

	free(graph);
	free(pq);
	free(visited);
	return 0;
}

// AdjNode 반환
AdjNode* getAdjNode() {
	AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
	newNode->next = NULL;
	newNode->vertex = -1;
	newNode->weight = -1;
	return newNode;
}

// 그래프 초기화
void initGraph(Vertex* graph, int n) {
	for (int i = 0; i <= n; i++) {
		graph[i].d = 999999999;
		graph[i].p = -1;
		graph[i].AdjList = getAdjNode();
	}
}

//AdjNode 추가
void insertAdjNode(AdjNode* AdjList, int v, int w) {
	AdjNode* newNode = getAdjNode();
	newNode->next = AdjList->next;
	newNode->vertex = v;
	newNode->weight = w;
	AdjList->next = newNode;
}

// PQ에 원소 삽입
void insertPQ(Vertex* pq, int* n, int pointer, Vertex v) {
	(*n)++;
	v.pointer = pointer;
	pq[*n] = v;
	upHeap(pq, n, *n);
}

// upHeap (d 작은 원소를 위로)
void upHeap(Vertex* pq, int* n, int v) {
	int parent = v / 2;
	while (parent >= 1 && pq[parent].d > pq[v].d) {
		Vertex temp = pq[parent];
		pq[parent] = pq[v];
		pq[v] = temp;
		v = parent;
		parent = v / 2;
	}
}

// 아이템 제거 후 반환
Vertex removeMin(Vertex* pq, int* n) {
	Vertex ele = pq[1];
	pq[1] = pq[*n];
	(*n)--;
	downHeap(pq, n, 1);
	return ele;
}

// downHeap(d가 작은 것을 위로)
void downHeap(Vertex* pq, int* n, int v) {
	while (v * 2 <= *n) {
		int left = v * 2;
		int right = v * 2 + 1;

		int smaller = left;
		if (right <= *n && pq[smaller].d > pq[right].d) 
			smaller = right;

		if (pq[v].d <= pq[smaller].d) break;

		Vertex temp = pq[v];
		pq[v] = pq[smaller];
		pq[smaller] = temp;

		v = smaller;
	}
}

// pq에서 pointer를 가르키는 원소의 w를 설정
void setKey(Vertex* pq, int* n, int pointer, int w) {
	for (int i = 1; i <= *n; i++) {
		if (pq[i].pointer == pointer) {
			pq[i].d = w;
			upHeap(pq, n, i);
			return;
		}
	}
}
