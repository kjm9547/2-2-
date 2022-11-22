#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
	
} GraphType;
struct Edge {			// ������ ��Ÿ���� ����ü
	int start, end, weight;
};



int selected[MAX_VERTICES];
int distance[MAX_VERTICES];
Edge* e;
void create(int n) {
	e = (Edge*)malloc(sizeof(Edge) * n);
}
int stack = 0;
// �ּ� dist[v] ���� ���� ������ ��ȯ
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

		//�� A������ ���Ӱ� MST�� �߰��Ǿ�� �� 
		//vertex�� edge�� ���� ������ �����ؾ� �Ѵ�.
		//�� ������ 1)�� ������ Data Structure�� �߰��϶�. 
		
		printf("���� %d �߰�\n", u);
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
