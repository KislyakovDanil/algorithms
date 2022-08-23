#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct edge {
    edge(int f, int t, int d): from(f), to(t), dist(d){};
    int from;
    int to;
    int dist;
};

// Функция "сравнения" двух ребер, используемая для сортировки
struct comp{
    bool operator()(edge& a,edge& b) {
        return a.dist > b.dist;
    }
};

int Kruskal(priority_queue<edge, vector<edge>, comp>& edges, int num_v){// Алгоритм Крускала
    int count = 0;
    vector<vector<int>> vertex_groups(num_v);
    int num_vertex_groups = 0;
    vector<int> visited(num_v,0);
    while(!edges.empty()){ // пока не прошли все ребра
        edge min_edge = edges.top();
        edges.pop();
        int from = visited[min_edge.from];
        int to = visited[min_edge.to];
        if (to== 0 && from == 0){
            visited[min_edge.to] = ++num_vertex_groups;
            visited[min_edge.from] = num_vertex_groups;
            vertex_groups[num_vertex_groups].push_back(min_edge.from);
            vertex_groups[num_vertex_groups].push_back(min_edge.to);
            count += min_edge.dist;
        } else if (to == 0 && from != 0){
            visited[min_edge.to] = from;
            vertex_groups[from].push_back(min_edge.to);
            count += min_edge.dist;
        } else if(from == 0 && to != 0){
            visited[min_edge.from] = to;
            vertex_groups[to].push_back(min_edge.from);
            count += min_edge.dist;
        } else if ( from != to){
            for (int i: vertex_groups[to]){
                vertex_groups[from].push_back(i);
                visited[i] = from;
            }
            count += min_edge.dist;
        }
    }
    return count;
}

int main(){
    int n, m;
    cin >> n >> m;
    priority_queue<edge, vector<edge>, comp> edges;
    for(int i = 0; i < m; i++) {
        int from, to, dist;
        cin >> from >> to >> dist;
        edges.push(edge(from,to,dist));
    }
    cout << Kruskal(edges, n+1);
    return 0;
}