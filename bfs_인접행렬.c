#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

void enqueue(int* q, int* f, int* l, int e);
int dequeue(int* q, int* f, int* l);

void bfs(int **g, int n, int s) {

	int *visited = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 0; i <= n; i++) visited[i] = 0;

	// queue 생성 (크기 n)
	int* q = (int*)malloc(sizeof(int) * (n + 1));
	int f = 0, l = 0; // 같으면 빈 큐

	visited[s] = 1;
	enqueue(q, &f, &l, s);
	while (f != l) {
		int z = dequeue(q, &f, &l);
		printf("%d\n", z);

		for (int i = 1; i <= n; i++) {
			if (g[z][i] == 1 && visited[i] == 0) {
				visited[i] = 1;
				enqueue(q, &f, &l, i);
			}
		}
	}

	free(visited);
	free(q);
}

int main() {
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);

	// 그래프 초기화
	int** g = (int**)malloc(sizeof(int*) * (n + 1));
	for (int i = 0; i <= n; i++)
		g[i] = (int*)malloc(sizeof(int) * (n + 1));

	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			g[i][j] = 0;

	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u][v] = 1;
		g[v][u] = 1;
	}

	
	bfs(g, n, s);

	for (int i = 0; i <= n; i++)
		free(g[i]);
	free(g);
	return 0;
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
