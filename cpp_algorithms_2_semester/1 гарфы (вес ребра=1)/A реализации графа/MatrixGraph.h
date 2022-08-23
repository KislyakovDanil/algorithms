#pragma once
#include "IGraph.h"
using namespace std;

class CMatrixGraph: public IGraph {
public:
	CMatrixGraph(int n);
	CMatrixGraph(const IGraph*);

	void AddEdge(int from, int to);

	int VerticesCount() const;

	void GetNextVertices(int vertex, vector<int>& vertices) const;
	void GetPrevVertices(int vertex, vector<int>& vertices) const;
private:
	vector<vector<int>> Matrix;
};