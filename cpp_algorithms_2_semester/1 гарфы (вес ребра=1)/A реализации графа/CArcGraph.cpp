#include "ArcGraph.h"
#include <iostream>
using namespace std;

CArcGraph::CArcGraph(int n): edges(), NumVert(n) {}

CArcGraph::CArcGraph(const IGraph* BaseGraph): CArcGraph(BaseGraph->VerticesCount()) {
	for (int i = 0; i < NumVert; ++i) {
		vector<int> vertices;
		BaseGraph->GetNextVertices(i, vertices);
		for (int j = 0; j < vertices.size(); ++j) {
			edges.push_back(make_pair(i,j));
		}
	}
}

void CArcGraph::AddEdge(int from, int to) {
	if (0 <= from && from < NumVert && 0 <= to && to < NumVert) {
		edges.push_back(make_pair(from, to));
	}
}

int CArcGraph::VerticesCount() const {
	return NumVert;
}

void CArcGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
	for (pair<int,int> i : edges) {
		if (i.first == vertex) {
			vertices.push_back(i.second);
		}
	}
}

void CArcGraph::GetPrevVertices(int vertex, vector<int>& vertices) const {
	for (pair<int,int> i : edges) {
		if (i.second == vertex) {
			vertices.push_back(i.first);
		}
	}
}