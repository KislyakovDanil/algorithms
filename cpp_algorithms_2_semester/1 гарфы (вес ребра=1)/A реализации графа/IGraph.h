#pragma once
#include<vector>
using namespace std;

struct IGraph {
	virtual ~IGraph() {}

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

	virtual void GetNextVertices(int vertex, vector<int>& vertices) const = 0;
	virtual void GetPrevVertices(int vertex, vector<int>& vertices) const = 0;
};
