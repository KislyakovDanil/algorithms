#pragma once
#include "IGraph.h"
#include <vector>
#include <list>
using namespace std;

class CListGraph: public IGraph {
public:
	CListGraph(int n);
	CListGraph(const IGraph*);

	void AddEdge(int from, int to) override;

	int VerticesCount() const;

	void GetNextVertices(int vertex, vector<int>& vertices) const;
	void GetPrevVertices(int vertex, vector<int>& vertices) const;
private:
	vector<list<int>> edges;
};