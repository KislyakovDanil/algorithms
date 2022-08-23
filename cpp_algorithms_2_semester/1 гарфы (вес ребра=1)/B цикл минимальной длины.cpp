#include <iostream>
#include <queue>
#include <vector>
using namespace std;
//алгоритм за O(VE)

int MinCycle(int start, vector<vector<int>>& edges){ //О(Е)
    queue<int> q;
    q.push(start);
    vector<bool> IsVisited(edges.size(), false);
    IsVisited[start] = true;
    vector<int> distance(edges.size(), 0);
    vector<int> pred(edges.size(), -1);
    int minC = 12000; // длина минимального цикла
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < edges[v].size(); ++i){
            if (!IsVisited[edges[v][i]]) {
                pred[edges[v][i]] = v;
                distance[edges[v][i]] = distance[v] + 1;
                IsVisited[edges[v][i]] = true;
                q.push(edges[v][i]);
            } else if ((edges[v][i] != pred[v]) && ((distance[v] + distance[edges[v][i]] + 1) < minC)){
                minC = distance[v] + distance[edges[v][i]] + 1;
            }
        }
    }
    return minC;
}

int main() {
    int v = 0, e = 0;
    cin >> v >> e;
    vector<vector<int>> edges(v);
    for (int i = 0; i < e; ++i){
        int v1;
        int v2;
        cin >> v1 >> v2;
        edges[v1].push_back(v2);
        edges[v2].push_back(v1);
    }
    int minC = 12000;
    for(int i = 0; i < v; ++i) {
        minC = min(minC,MinCycle(i, edges));
        if(minC == 3){
            break;
        }
    }
    if (minC == 12000){
        cout << -1;
    } else {
        cout << minC;
    }
    return 0;
}