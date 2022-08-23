#include "ListGraph.h"
#include <iostream>
using namespace std;

CListGraph::CListGraph(int n): edges(n) {}

CListGraph::CListGraph(const IGraph* Graph): CListGraph(Graph->VerticesCount()) {
    for (int i = 0; i < edges.size(); ++i) {
        vector<int> vertices;
        Graph->GetNextVertices(i, vertices);
        for (int j : vertices){
            edges[i].push_back(j);
        }
    }
}

void CListGraph::AddEdge(int from, int to) {
    bool presence = false;//наличие to в edges[from]
    for(int i : edges[from]){
        if(i == to){
            presence = true;
        }
    }
    if (!presence && 0 <= from && from < edges.size() && 0 <= to && to < edges.size()) {
        edges[from].push_back(to);
    }
}

int CListGraph::VerticesCount() const {
    return edges.size();
}

void CListGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
    for (int i : edges[vertex]) {
        vertices.push_back(i);
    }
}

void CListGraph::GetPrevVertices(int vertex, vector<int>& vertices) const {
    for (int i = 0; i < edges.size(); ++i) {
        for (int j : edges[i]) {
            if (j == vertex) {
                vertices.push_back(i);
            }
        }
    }
}