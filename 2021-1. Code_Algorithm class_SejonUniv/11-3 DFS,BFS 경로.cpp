#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

typedef struct edge {
	int p;
	int q;
	char label;
}edge;

typedef struct vertex {
	int v;
	int isVisited;
}vertex;

vertex* vert;
edge* edges;
int** ad;
int n, m;

int start, end;
int stack[1000] = { 0, };
int stackEnd = 0;

int parent[1000] = { 0, };

int queue[1000];

void insertEdge(int a, int b);
void Bfs(int v);
void Bfs2(int start, int end);
void Dfs(int start, int end);

int main(void) {

	int a, b;

	int s, v = 0, w = 0;

	scanf("%d %d %d", &n, &m, &s);

	vert = (vertex*)malloc(n * sizeof(vertex));
	edges = (edge*)malloc(m * sizeof(edge));
	ad = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
		ad[i] = (int*)malloc(n * sizeof(int));

	//vertex 초기화
	for (int i = 0; i < n; i++) {
		vert[i].v = i + 1;
		vert[i].isVisited = 0;
	}

	//edge 초기화
	for (int i = 0; i < m; i++) {
		edges[i].p = -1;
		edges[i].q = -1;
		edges[i].label = 'f';
	}

	// 인접 행렬 초기화
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ad[i][j] = -1;
		}
	}

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		insertEdge(a, b);
	}

	//// 시작 index찾기
	//for (int i = 0; i < n; i++) {
	//	if (vert[i].v == s) {
	//		v = i;
	//		break;
	//	}
	//}

	printf("start : ");
	scanf("%d", &start);

	printf("end : ");
	scanf("%d", &end);


	// 시작 index찾기
	for (int i = 0; i < n; i++) {
		if (vert[i].v == start) {
			v = i;
			break;
		}
	}

	// 끝 index찾기
	for (int j = 0; j < n; j++) {
		if (vert[j].v == end) {
			w = j;
			break;
		}
	}

	//Dfs(v,w);
	//for (int i = 0; i < stackEnd; i++)
	//	printf(" %d", stack[i]);

	Bfs2(v,w);

}

int q = 0;

// dfs 경로찾기
void Dfs(int start, int end) {

	int tmp;
	vert[start].isVisited = 1;

	stack[stackEnd++] = vert[start].v;

	for (int i = 0; i < stackEnd; i++)
		printf(" %d", stack[i]);
	printf("\n");

	if (start == end) {
		q = 1;
		return;
	}

	for (int i = 0; i < n; i++) {
		if (ad[start][i] != -1 && vert[i].isVisited == 0 && q == 0) {
			Dfs(i,end);
		}
	}

	// 맨끝까지 봤는데 값을 못찾은 경우이다. stack--
	if (q == 0)
		stackEnd--;
}

// BFS를 통한 최단 경로
void Bfs2(int start, int end) {

	int front = 0, rear = 0;
	int pop,tmp;

	stack[stackEnd++] = vert[start].v;

	queue[0] = start;
	rear++;
	vert[start].isVisited = 1;

	tmp = 0;

	while (front < rear) {
		pop = queue[front++];

		for (int i = 0; i < n; i++) {
			if (ad[pop][i] != -1 && vert[i].isVisited == 0) {

				queue[rear] = i;
				rear++;
				vert[i].isVisited = 1;

				// 부모 배열에 부모 index 저장
				parent[++tmp] = front - 1;

				//break하기위해
				if (end == i) {
					rear = -1;
					break;
				}

			}
		}
	}

	int result = tmp,k=0;
	int arr[100] = { 0, };

	while (result!=start) {
		arr[k++] = vert[result].v;
		result = parent[result];
	}

	printf(" %d", vert[start].v);

	for (int t = k - 1; t >= 0; t--)
		printf(" %d", arr[t]);
}

void insertEdge(int a, int b) {

	int i = 0;
	while (1) {
		if (edges[i].p == -1) {

			edges[i].p = a - 1;
			edges[i].q = b - 1;

			ad[a - 1][b - 1] = i;
			ad[b - 1][a - 1] = i;
			return;
		}
		i++;
	}
}


void Bfs(int v) {

	int stack[100] = { 0, };
	int tmp[100] = { 0, };
	int i = 1, v2, tmpIdx;

	vert[v].isVisited = 1;
	stack[0] = v;

	while (i != 0) {

		for (int j = 0; j < i; j++) {
			printf("%d\n", vert[stack[j]].v);
			tmp[j] = stack[j];
		}

		// 반복의 시작일때 i 값을 0으로 초기화한다.
		int len = i;
		i = 0;

		// stack에 있던 값들을 tmp에 저장하고 tmp를 돈다
		// 그 다음 레벨의 노드들을 stack 저장.
		for (int l = 0; l < len; l++) {

			v = tmp[l];

			for (int j = 0; j < n; j++) {

				if (ad[v][j] != -1) {

					// edge idx
					tmpIdx = ad[v][j];

					if (edges[tmpIdx].label == 'f') {

						// 간선의 반대쪽 vertex, v가 아닌 vertex
						v2 = j;

						if (vert[v2].isVisited == 0) {
							edges[tmpIdx].label = 't';
							vert[v2].isVisited = 1;
							stack[i] = v2;
							i++;
						}
						else {
							// 교차간선
							edges[tmpIdx].label = 'c';
						}

					}

				}

			}


		}
	}
}