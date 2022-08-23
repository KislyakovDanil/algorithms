#include "SetGraph.h"
#include <iostream>
using namespace std;

CSetGraph::CSetGraph(int n): edges(n) {}

CSetGraph::CSetGraph(const IGraph* BaseGraph): CSetGraph(BaseGraph->VerticesCount()) {
	for (int i = 0; i < edges.size(); ++i) {
		vector<int> vertices;
		BaseGraph->GetNextVertices(i, vertices);
		for (int j : vertices){
			edges[i].insert(j);
		}
	}
}

void CSetGraph::AddEdge(int from, int to) {
	if (0 <= from && from < edges.size() && 0 <= to && to < edges.size()) {
		edges[from].insert(to);
	}
}

int CSetGraph::VerticesCount() const {
	return edges.size();
}

void CSetGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
	for (int i : edges[vertex]) {
		vertices.push_back(i);
	}
}

void CSetGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
	for (auto i = 0; i < edges.size(); ++i) {
		for (int j : edges[i]) {
			if (j == vertex) {
				vertices.push_back(i);
			}
		}
	}
}