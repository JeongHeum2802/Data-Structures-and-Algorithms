#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
	int u;
	int v;
	int w;
}Edge;

int main() {
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);

	// 엣지 리스트 초기화
	Edge* edges = (Edge*)malloc(sizeof(Edge) * m);

	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges[i].u = u;
		edges[i].v = v;
		edges[i].w = w;
	}

	// 벨만 포드
	int* d = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 0; i <= n; i++) d[i] = 999999999;
	d[s] = 0;
	
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < m; j++) {
			int u, v, w;
			u = edges[j].u; v = edges[j].v; w = edges[j].w;

			if (d[u] == 999999999) continue; // 출발 노드가 도달 불가 노드면 패스

			if (d[v] > d[u] + w)
				d[v] = d[u] + w;
		}
	}

	// 출력
	for (int i = 1; i <= n; i++) {
		if (d[i] == 999999999 || i == s)
			continue;
		printf("%d %d\n", i, d[i]);
	}

	// 할당 해제
	free(edges);
	free(d);
	return 0;
}
