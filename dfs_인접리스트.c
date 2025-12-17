#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct AdjNode {
	int z;
	struct AdjNode* next;
} AdjNode;

typedef struct Vertex {
	struct AdjNode* AdjList;
} Vertex;

// 인접노드 반환
AdjNode* getAdjNode();
// 그래프 간선 추가
void addEdge(Vertex* g, int u, int v);
// 인접리스트에 노드 추가 (오름차순)
void addAdjNode(AdjNode* header, int v);

void freeGraph(Vertex* g, int n) {
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
}

void dfs(Vertex* g, int s, int *visited);

int main() {
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);

	// 그래프 초기화
	Vertex* g = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
	for (int i = 0; i <= n; i++)
		g[i].AdjList = getAdjNode();
	 
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(g, u, v);
	}

	int* visited = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 0; i <= n; i++) visited[i] = 0;
	dfs(g, s, visited);


	freeGraph(g, n);
	free(visited);
	return 0;
}

AdjNode* getAdjNode() {
	AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
	newNode->z = -1;
	newNode->next = NULL;
	return newNode;
}
// 그래프 간선 추가
void addEdge(Vertex* g, int u, int v) {
	addAdjNode(g[u].AdjList, v);
	addAdjNode(g[v].AdjList, u);
}

// 인접리스트에 노드 추가 (오름차순)
void addAdjNode(AdjNode* header, int v) {
	AdjNode* q = header;
	AdjNode* p = header->next;

	while (p != NULL && p->z < v) {
		p = p->next;
		q = q->next;
	}

	AdjNode* newNode = getAdjNode();
	newNode->z = v;

	newNode->next = p;
	q->next = newNode;
}

void dfs(Vertex* g, int s, int *visited) {
	visited[s] = 1;
	printf("%d\n", s);

	AdjNode* p = g[s].AdjList->next;
	while (p != NULL) {
		if (visited[p->z] == 0)
			dfs(g, p->z, visited);
		p = p->next;
	}
}
