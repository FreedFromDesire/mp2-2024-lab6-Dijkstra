#pragma once


#include <gtest.h>
#include "dijkstra.h"


TEST(Graph, generate_default) {
	ASSERT_NO_THROW(Graph gr(0));
}

TEST(Graph, get_by_matrix) {
	int n = 5;
	Graph gr(n);
	Vector<Vector<double>> a(n, Vector<double>(n));
	a[0][1] = 1;
	ASSERT_NO_THROW(gr.get_by_matrix(a));
}

TEST(Graph, get_by_list) {
	int n = 5;
	Graph gr(n);
	Vector<Vector<int>> a(n);
	Vector<Vector<double>> w(n);

	a[0].push_back(5);
	w[0].push_back(1);
	
	ASSERT_NO_THROW(gr.get_by_list(a, w));
}

TEST(Graph, get_connected_graph_by_matrix) {
	int n = 5;
	Graph gr(n);
	Vector<Vector<double>> a(n, Vector<double>(n));
	a[0][1] = 1;
	a[1][2] = 1;
	a[2][3] = 1;
	a[3][4] = 1;
	a[4][0] = 1;

	gr.get_by_matrix(a);
	ASSERT_EQ(gr.check_connect(), 1);
}

TEST(Graph, get_not_connected_graph_by_matrix) {
	int n = 5;
	Graph gr(n);
	Vector<Vector<double>> a(n, Vector<double>(n));
	a[0][1] = 1;
	a[1][2] = 1;
	a[2][3] = 1;
	a[3][4] = 1;

	gr.get_by_matrix(a);
	ASSERT_EQ(gr.check_connect(), 0);
}

TEST(Graph, get_connected_graph_by_list) {
	int n = 5;
	Graph gr(n);
	Vector<Vector<int>> a(n);
	Vector<Vector<double>> w(n);

	a[0].push_back(1);
	w[0].push_back(1);
	a[1].push_back(2);
	w[1].push_back(1);
	a[2].push_back(3);
	w[2].push_back(1);
	a[3].push_back(4);
	w[3].push_back(1);
	a[4].push_back(0);
	w[4].push_back(1);

	gr.get_by_list(a, w);
	ASSERT_EQ(gr.check_connect(), 1);
}

TEST(Graph, get_not_connected_graph_by_list) {
	int n = 5;
	Graph gr(n);
	Vector<Vector<int>> a(n);
	Vector<Vector<double>> w(n);

	a[0].push_back(1);
	w[0].push_back(1);
	a[1].push_back(2);
	w[1].push_back(1);
	a[2].push_back(3);
	w[2].push_back(1);
	a[3].push_back(4);
	w[3].push_back(1);

	gr.get_by_list(a, w);
	ASSERT_EQ(gr.check_connect(), 0);
}

TEST(Graph, check_dijkstra_get_by_matrix) {
	int n = 5;
	Graph gr(n);
	Vector<Vector<double>> a(n, Vector<double>(n));
	a[0][1] = 1;
	a[1][2] = 1;
	a[2][3] = 1;
	a[3][4] = 1;

	gr.get_by_matrix(a);

	Vector<double> ans = gr.dijkstra(0);
	for (int i = 0; i < n; i++) {
		ASSERT_EQ(ans[i], i);
	}
}

TEST(Graph, check_dijkstra_get_by_list) {
	int n = 5;
	Graph gr(n);
	Vector<Vector<int>> a(n);
	Vector<Vector<double>> w(n);

	a[0].push_back(1);
	w[0].push_back(1);
	a[1].push_back(2);
	w[1].push_back(1);
	a[2].push_back(3);
	w[2].push_back(1);
	a[3].push_back(4);
	w[3].push_back(1);

	gr.get_by_list(a, w);

	Vector<double> ans = gr.dijkstra(0);
	for (int i = 0; i < n; i++) {
		ASSERT_EQ(ans[i], i);
	}
}

TEST(Graph, generate_random_connected_graph_1) {
	int n = 5;
	Graph gr(n);

	gr.generate_random(5, 0);

	ASSERT_EQ(gr.check_connect(), 1);
}

TEST(Graph, generate_random_connected_graph_2) {
	int n = 5;
	Graph gr(n);
	for (int i = 0; i < n * n; i++) {
		gr.generate_random(5, i);
		ASSERT_EQ(gr.check_connect(), 1);
	}
}