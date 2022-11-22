#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
	
} GraphType;
struct Edge {			// 간선을 나타내는 구조체
	int start, end, weight;
};



int selected[MAX_VERTICES];
int distance[MAX_VERTICES];
Edge* e;
void create(int n) {
	e = (Edge*)malloc(sizeof(Edge) * n);
}
int stack = 0;
// 최소 dist[v] 값을 갖는 정점을 반환
Edge get_min_vertex(int n)
{
	
	int v, i;
	
	for (i = 0; i < n; i++)
	{
		if (!selected[i]) {
			v = i;
			break;
		}
	}
	//e.start = v;v=1
	for (i = 0; i < n; i++) {
		if (!selected[i] && (distance[i] < distance[v])) {
			v = i;
			
		}
	}
	//e[stack].start = e[stack - 1].end;
	e[stack].end = v;
	if (stack != 0) {
		e[stack].start = e[stack - 1].end;

	}
	else {
		e[stack].start = v;
	}

	
	printf("%d _ %d", e[stack].start, e[stack].end);
	stack++;
	return e[stack-1];
}
//
void prim(GraphType* g, int s)
{
	int i, u, v;
	Edge test;
	for (u = 0; u < g->n; u++)
		distance[u] = INF;
	distance[s] = 0;
	for (i = 0; i < g->n; i++) {
		test = get_min_vertex(g->n);
		u = test.end;
		selected[u] = TRUE;
		if (distance[u] == INF) return;

		//의 A에서는 새롭게 MST에 추가되어야 할 
		//vertex와 edge에 대한 정보를 저장해야 한다.
		//이 정보를 1)로 선언한 Data Structure에 추가하라. 
		
		printf("정점 %d 추가\n", u);
		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF)
				if (!selected[v] && g->weight[u][v] < distance[v])
				{
					if (u == 0) {
						e[0].weight = distance[1];
					}
					distance[v] = g->weight[u][v];
					e[v].weight = g->weight[u][v];
				}
		
		
	}
	
}
int main(void)
{
	GraphType g = { 7,
	{{ 0, 29, INF, INF, INF, 10, INF },
	{ 29,  0, 16, INF, INF, INF, 15 },
	{ INF, 16, 0, 12, INF, INF, INF },
	{ INF, INF, 12, 0, 22, INF, 18 },
	{ INF, INF, INF, 22, 0, 27, 25 },
	{ 10, INF, INF, INF, 27, 0, INF },
	{ INF, 15, INF, 18, 25, INF, 0 } }
	};
	create(g.n);
	prim(&g, 0);
	
	for (int i = 0; i < 7; i++) {
		
		printf("start %d >>> end %d\t weight:%d\n", e[i].start, e[i].end, e[e[i].end].weight);
	}
	return 0;
}
