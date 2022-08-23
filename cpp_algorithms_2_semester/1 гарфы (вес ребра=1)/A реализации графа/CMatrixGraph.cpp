#include "MatrixGraph.h"
#include <iostream>
using namespace std;

CMatrixGraph::CMatrixGraph(int n): Matrix(n,vector<int>(n,0)) {}

CMatrixGraph::CMatrixGraph(const IGraph* BaseGraph): CMatrixGraph(BaseGraph->VerticesCount()) {
	for (int i = 0; i < Matrix.size(); ++i) {
		vector<int> vertices;
		BaseGraph->GetNextVertices(i, vertices);
		for (int j = 0; j < vertices.size(); ++j) {
			Matrix[i][j] = 1;
		}
	}
}

void CMatrixGraph::AddEdge(int from, int to) {
	if (0 <= from && from < Matrix.size() && 0 <= to && to < Matrix.size()) {
		Matrix[from][to] = 1;
	}
}

int CMatrixGraph::VerticesCount() const {
	return Matrix.size();
}

void CMatrixGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
	for (int i = 0; i < Matrix.size(); ++i) {
		if (Matrix[vertex][i] == 1) {
			vertices.push_back(i);
		}
	}
}

void CMatrixGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
	for (int i = 0; i < Matrix.size(); ++i) {
		if (Matrix[i][vertex] == 1) {
			vertices.push_back(i);
		}
	}
}