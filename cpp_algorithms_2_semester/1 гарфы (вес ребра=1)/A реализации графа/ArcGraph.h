#pragma once
#include "IGraph.h"
#include <vector>
#include <pair>
using namespace std;

class CArcGraph: public IGraph {
public:
	CArcGraph(int n);
	CArcGraph(const IGraph*);

	void AddEdge(int from, int to);

	int VerticesCount() const override;

	void GetNextVertices(int vertex, vector<int>& vertices) const;
	void GetPrevVertices(int vertex, vector<int>& vertices) const;
private:
	vector<pair<int,int>> edges;
	int NumVert;
};