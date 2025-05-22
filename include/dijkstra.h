#pragma once

#include <iostream>
#include "dheap.h"
#include "vector.h"
#include <random>

const double eps = 1e-15;

Vector<Vector<int>> generate_connected_graph_matrix(int n, int m, bool is_oriented) {
	if (is_oriented) {
		m = std::max(m, n);
		m = std::min(m, n * n - n);
	}
	else {
		m = std::max(m, n - 1);
		m = std::min(m, n * (n - 1) / 2);
	}
	

	Vector<Vector<int>> graph(n, Vector<int>(n, 0));

	Vector<Vector<bool>> dsu;
	int edges_added = 0;
	random_device rd;
	mt19937 gen(rd());

	int u = 0;

	Vector<int> perm(n);

	for (int i = 0; i < n; i++) {
		perm[i] = i;
	}

	for (int i = 0; i < n; i++) {
		uniform_int_distribution<> dis(i, n - 1);
		std::swap(perm[i], perm[dis(gen)]);
	}

	for (int i = 1; i < n + (is_oriented); i++) {
		//std::cout << (i - 1) << ' ' << i << '\n';
		graph[perm[i - 1]][perm[i % n]] = 1;
		if (!is_oriented)
			graph[perm[i]][perm[i - 1]] = 1;
	}


	int remaining_edges = m - n + (is_oriented == 0);
	if (remaining_edges > 0) {

		Vector<pair<int, int>> possible_edges;
		for (int u = 0; u < n; u++) {
			for (int v = 0; v < n; v++) {
				if (graph[u][v] == 0 && u != v) {
					possible_edges.push_back({ u, v });
				}
			}
		}

		int size = possible_edges.size();
		for (int i = 0; i < remaining_edges; i++) {
			uniform_int_distribution<> dis(i, size - 1);
			std::swap(possible_edges[i], possible_edges[dis(gen)]);
		}

		for (int i = 0, c = 0; c < remaining_edges; i++, c++) {
			int u = possible_edges[i].first;
			int v = possible_edges[i].second;
			if (graph[u][v] == 1 && !is_oriented) {
				c--;
			}
			graph[u][v] = 1;
			if (!is_oriented)
				graph[v][u] = 1;
		}
	}

	return graph;
}


class Graph {
	Vector<Vector<int>> adj;
	Vector<Vector<double>> weight;
	
	int n;

	void dfs(int v, Vector<int>& was) {
		was[v]++;
		for (int i = 0; i < adj[v].size(); i++)
			if (was[adj[v][i]] != was[v])
				dfs(adj[v][i], was);
	}

public:
	Graph(int n) {
		this->n = n;
		adj.resize(n);
		weight.resize(n);
	}

	void get_by_matrix(const Vector<Vector<double>>& a) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (abs(a[i][j]) > 1e-15) {
					adj[i].push_back(j);
					weight[i].push_back(a[i][j]);
				}
			}
		}
	}

	bool check_connect() {
		Vector<int> was(n, 0);
		for (int i = 0; i < n; i++) {
			dfs(i, was);
			for (int j = 0; j < n; j++)
				if (was[j] != i + 1)
					return 0;
		}
		return 1;
	}

	void get_by_list(const Vector<Vector<int>>& a, const Vector<Vector<double>>& w) {
		for (int i=0;i<n;i++)
			adj[i] = a[i];
		for (int i=0;i<n;i++)
			weight[i] = w[i];
	}

	void generate_random(int c, bool is_oriented) {
		Vector<Vector<int>> a = generate_connected_graph_matrix(n,c, is_oriented);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << a[i][j] << ' ';
			}
			std::cout << '\n';
		}

		random_device rd;
		mt19937_64 gen(rd());
		uniform_real_distribution<long double> dis(0.01, 1e3);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (a[i][j] == 1) {
					adj[i].push_back(j);
					weight[i].push_back(dis(gen));
				}
			}
		}
	}

	Vector<double> dijkstra(int start) {
		Vector<double> dist(n, numeric_limits<double>::infinity());
		dist[start] = 0;

		BinaryHeap heap;
		heap.insert(start, 0);

		while (!heap.empty()) {

			pair<int, double> pr = heap.extractMin();
			int u = pr.first;
			double current_dist = pr.second;

			if (current_dist > dist[u]) {
				continue;
			}

			for (size_t i = 0; i < adj[u].size(); ++i) {
				int v = adj[u][i];
				double wght = weight[u][i];

				if (dist[v] > dist[u] + wght) {
					dist[v] = dist[u] + wght;
					heap.decreaseKey(v, dist[v]);
				}
			}
		}

		return dist;
	}

	void display() {
		for (int i = 0; i < n; i++) {
			std::cout << "Вершина " << i << " : ";
			for (int j = 0; j < adj[i].size(); j++) {
				std::cout << '{' << adj[i][j] << ", " << weight[i][j] << "}";
				if (j != adj[i].size() - 1)
					std::cout << ',';
				std::cout << ' ';
			}
			std::cout << '\n';
		}
	}
};