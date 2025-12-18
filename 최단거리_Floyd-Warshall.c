#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, m;

	scanf("%d %d", &n, &m);
	
	int** graph = (int**)malloc(sizeof(int*) * (n + 1));
	for (int i = 0; i <= n; i++) {
		graph[i] = (int*)malloc(sizeof(int) * (n + 1));
		for (int j = 0; j <= n; j++) {
			if (i == j) graph[i][j] = 0;
			else graph[i][j] = 999999999;
		}
	}

	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		graph[u][v] = w;
		graph[v][u] = w;
	}


	int** d = (int**)malloc(sizeof(int*) * (n + 1));
	for (int i = 0; i <= n; i++) {
		d[i] = (int*)malloc(sizeof(int) * (n + 1));
		for (int j = 0; j <= n; j++)
			d[i][j] = graph[i][j];
	}

	for (int k = 1; k <= n; k++) {
		for (int u = 1; u <= n; u++)
			for (int v = 1; v <= n; v++) {
				if (d[u][k] + d[k][v] < d[u][v])
					d[u][v] = d[u][k] + d[k][v];
			}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			printf(" %d", d[i][j]);
		printf("\n");
	}

	// 할당 해제
	for (int i = 0; i <= n; i++) {
		free(graph[i]);
		free(d[i]);
	}
	free(graph);
	free(d);
}
