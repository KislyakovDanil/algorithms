#pragma once
#include "IGraph.h"
#include <vector>
#include <unordered_set>
using namespace std;

class CSetGraph: public IGraph {
public:
	CSetGraph(int n);
	CSetGraph(const IGraph*);

	void AddEdge(int from, int to);

	int VerticesCount() const override;

	void GetNextVertices(int vertex, vector<int>& vertices) const;
	void GetPrevVertices(int vertex, vector<int>& vertices) const;
private:
	vector<unordered_set<int>> edges;
};