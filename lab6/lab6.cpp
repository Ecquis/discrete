#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <ctime>

#define inf 100000

using namespace std;

struct Edges {
	int u, v, w;
};

// ----------- Дейкстра ------------ //

const int verts_count = 10;
int src = 0, dest = 0;
int min, min_index;
//
int minDistance(int distances[], bool processed_verts[])
{
	min = inf, min_index;

	for (int v = 0; v < verts_count; v++)
		if (processed_verts[v] == false && distances[v] <= min)
			min = distances[v], min_index = v;

	return min_index;
}

int dijkstra(int graph[verts_count][verts_count], int src)
{
	int distances[verts_count];
	bool processed_verts[verts_count];

	for (int i = 0; i < verts_count; i++) {
		distances[i] = inf;
		processed_verts[i] = false;
	}

	distances[src] = 0;

	int u;

	for (int count = 0; count < verts_count - 1; count++)
	{
		u = minDistance(distances, processed_verts);

		processed_verts[u] = true;

		for (int v = 0; v < verts_count; v++)
			if (!processed_verts[v] && graph[u][v] && distances[u] != inf && distances[u] + graph[u][v] < distances[v])
				distances[v] = distances[u] + graph[u][v];
	}
	return distances[dest];
}

// ----------------------------------------------------------------- //


// -------- Форд-Беллман -------- //

const int Vmax = 10;
const int Emax = Vmax * (Vmax - 1) / 2;

int i, j, n, e, start;

Edges edge[Emax];

int distances[Vmax];

void bellman_ford(int n, int s)
{
	int i, j;

	for (i = 0; i < n; i++) distances[i] = inf;
	distances[s] = 0;

	for (i = 0; i < n - 1; i++)
		for (j = 0; j < e; j++)
			if (distances[edge[j].v] + edge[j].w < distances[edge[j].u])
				distances[edge[j].u] = distances[edge[j].v] + edge[j].w;
}

// --------------------------------------------------------------------- //

int main()
{
	// инициализация
	src = 0;
	dest = 1;

	// установка начальных значений
	int graph[verts_count][verts_count] = { {0, 4, 0, 0, 0, 0, 0, 8, 0, 0},
						{4, 0, 8, 0, 0, 0, 0, 11, 0, 0},
						{0, 8, 0, 7, 0, 4, 0, 0, 2, 0},
						{0, 0, 7, 0, 9, 14, 0, 0, 0, 1},
						{0, 0, 0, 9, 0, 10, 0, 0, 0, 12},
						{0, 0, 4, 14, 10, 0, 2, 0, 0, 15},
						{0, 0, 0, 0, 0, 2, 0, 1, 6, 0},
						{8, 11, 0, 0, 0, 0, 1, 0, 7, 0},
						{0, 0, 2, 0, 0, 0, 6, 7, 0, 0}
	};

	// основной алгоритм
	float sum = 0, temp;
	float st_time;
	for (int loop = 0; loop < 10; loop++) {
		st_time = clock();
		for (int st = 0; st < 100000; st++) {
			dijkstra(graph, src);
		}
		temp = clock() - st_time;
		cout << temp << " ms\n";
		sum += temp;
	}
	cout << "Average time: " << sum / 10 << " ms\n";

	// ------------------- //

	// инициализация переменных
	int w;
	int n = 10;
	e = 1;

	// установка начальных значений
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
				edge[e].v = i;
				edge[e].u = j;
				edge[e].w = e;
				e++;
		}

	cout << "-----------------------\n";
	// основной алгоритм
	for (int loop = 0; loop < 10; loop++) {
		st_time = clock();
		for (int st = 0; st < 100000; st++) {
			bellman_ford(n, start - 1);
		}
		temp = clock() - st_time;
		cout << temp << " ms\n";
		sum += temp;
	}
	cout << "Average time: " << sum / 10 << " ms\n";

	return 0;
}
