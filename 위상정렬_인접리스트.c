#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct AdjNode {
	int oppsite;
	struct AdjNode* next;
} AdjNode;

typedef struct Vertex {
	char name;
	AdjNode* inList;
	AdjNode* outList;
	int inNum;
} Vertex;


AdjNode* getAdjNode(); // 부착노드 반환
int index(Vertex* g, int n, char vName); // 이름의 매칭되는 index 찾기

void addEdge(Vertex* g, char u, char v, int n); // 방향 간선 추가
void addAdjNode(AdjNode* header, int z); // 부착리스트에 노드 추가
int* topologicalSort(Vertex* g, int n); // 위상정렬

void enqueue(int* q, int *f, int *l, int e);
int dequeue(int* q, int *f, int *l);


int main() {
	int n, m;
	scanf("%d", &n);
	
	// 그래프 초기화
	Vertex* g = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
	for (int i = 1; i <= n; i++) {
		scanf(" %c", &g[i].name);
		g[i].inNum = 0;
		g[i].inList = getAdjNode();
		g[i].outList = getAdjNode();
	}
	
	// 간선 연결
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		char u, v;
		scanf(" %c %c", &u, &v);
		addEdge(g, u, v, n);
	}

	// 위상정렬
	int* topOrder = topologicalSort(g, n);
	if (topOrder[0] == 0)
		printf("0\n");
	else {
		for (int i = 1; i <= n; i++) {
			printf("%c ", g[topOrder[i]].name);
		}
	}

	// 할당 해제
	for (int i = 1; i <= n; i++) {
		AdjNode* p = g[i].inList;
		AdjNode* q;
		while (p != NULL) {
			q = p->next;
			free(p);
			p = q;
		}

		p = g[i].outList;
		while (p != NULL) {
			q = p->next;
			free(p);
			p = q;
		}
	}
	free(g);
	free(topOrder);
	return 0;
}

AdjNode* getAdjNode() {
	AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
	newNode->oppsite = -1;
	newNode->next = NULL;

	return newNode;
}

int index(Vertex* g, int n, char vName) {
	for (int i = 1; i <= n; i++) {
		if (g[i].name == vName) {
			return i;
		}
	}
	return -1;
} 

void addEdge(Vertex* g, char u, char v, int n) {
	int index_u = index(g, n, u);
	int index_v = index(g, n, v);

	addAdjNode(g[index_u].outList, index_v);
	addAdjNode(g[index_v].inList, index_u);
	g[index_v].inNum++;
}

void addAdjNode(AdjNode* header, int z) {
	AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
	newNode->oppsite = z;
	newNode->next = header->next;
	header->next = newNode;
}

int* topologicalSort(Vertex* g, int n) {
	// 결과 배열
	int* topOrder = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 0; i <= n; i++)
		topOrder[i] = 0;

	// queue
	int* q = (int*)malloc(sizeof(int) * (n + 1));
	int l = 0, f = 0; // l == f => empty

	// 위상정렬
	int* in = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 1; i <= n; i++) {
		in[i] = g[i].inNum;
		if (in[i] == 0)
			enqueue(q, &f, &l, i);
	}


	int i = 1;
	while (f != l) {
		int u = dequeue(q, &f, &l);
		topOrder[i] = u;
		i++;
		AdjNode* p = g[u].outList->next;
		while (p != NULL) {
			in[p->oppsite]--;
			if (in[p->oppsite] == 0) {
				enqueue(q, &f, &l, p->oppsite);
			}
			p = p->next;
		}
	}
	if (i > n) topOrder[0] = 1; // 싸이클 판별

	free(q);
	free(in);
	return topOrder;
}

void enqueue(int* q, int* f, int* l, int e) {
	q[*l] = e;
	(*l)++;
}

int dequeue(int* q, int* f, int* l) {
	int a = q[*f];
	(*f)++;
	return a;
}
