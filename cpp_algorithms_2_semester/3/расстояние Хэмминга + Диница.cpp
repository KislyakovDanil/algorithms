#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct edge{
    edge(int c):capacity(c), flow(0){};
    int capacity;//вместимость ребра
    int flow;//поток, проход€щий через ребро
};

struct vert{
    vector<int> children = {};
    int first_undel = 0;// номера первых неудалЄнных рЄбер
};

void find_achievable(vector<int>& dist_from_start, vector<vector<edge>>& edges, vector<vert>& vertices){
    dist_from_start[0] = 0;
    queue<int> Q;
    Q.push(0);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < vertices[u].children.size(); ++i){
            int v = vertices[u].children[i];
            if ((edges[u][v].flow < edges[u][v].capacity) && dist_from_start[v] == 100000000){
                dist_from_start[v] = dist_from_start[u] + 1;
                Q.push(v);
            }
        }
    }
}

bool BFS(vector<vector<edge>>& edges, vector<int>& dist_from_start, vector<vert>& vertices){
    for (int i = 0; i < dist_from_start.size(); ++i){
        dist_from_start[i] = 100000000;
    }
    find_achievable(dist_from_start, edges, vertices);
    return dist_from_start[1] != 100000000;
}
int DFS(vector<vector<edge>>& edges, vector<int>& dist_from_start, int vert_num, int min_capacity, vector<vert>& vertices){//vert_num - номер вершины, min_capacity Ч минимальна€ пропускна€ способность дополн€ющей сети на пройденном dfs пути
    if (vert_num == 1 || min_capacity == 0) {
        return min_capacity;
    }
    for (int i = vertices[vert_num].first_undel; i < vertices[vert_num].children.size(); ++i){
        int u = vertices[vert_num].children[i];
        ++vertices[vert_num].first_undel;
        if (edges[vert_num][u].capacity <= edges[vert_num][u].flow) {//если ребро уже насыщено
            continue;
        }
        if (dist_from_start[u] == dist_from_start[vert_num] + 1){ //поиск во вспомогательной слоистой сети
            int delta =  DFS(edges, dist_from_start, u, min(min_capacity, edges[vert_num][u].capacity - edges[vert_num][u].flow), vertices);
            if (delta > 0){
                edges[vert_num][u].flow += delta; // насыщаем рЄбра по пути dfs
                edges[u][vert_num].flow -= delta;
                return delta;
            }
        }
    }
    return 0;
}

int Dinic(vector<vector<edge>>& edges, vector<vert>& vertices) {
    int max_flow = 0;
    vector<int> dist_from_start(edges.size(), 0);//рассто€ние от стартовой вершины
    while(BFS(edges, dist_from_start, vertices)) {
        for (int i = 0; i < vertices.size(); ++i){//???
            vertices[i].first_undel = 0;
        }
        int flow = 0;
        do {
            max_flow += flow;
            flow = DFS(edges, dist_from_start, 0, 100000000, vertices);
        } while (flow != 0);
    }
    return max_flow;
}

int build_graph(const vector<int>& s_v, const vector<int>& p_v, vector<vector<edge>>& edges, vector<vert>& vertices){
    int HamingDist = 0;
    int delta = p_v.size() - s_v.size();
    for(int i = 0; i < s_v.size(); ++i){
        for(int j = i; j <= i + delta; ++j){
            if (s_v[i] == 0){
                if(p_v[j] == 1){
                    HamingDist +=1;
                } else if(p_v[j] > 1) {
                    if (edges[0][p_v[j]].capacity == 0){
                        vertices[0].children.push_back(p_v[j]);
                    }
                    ++edges[0][p_v[j]].capacity;
                }
            } else if (s_v[i] == 1){
                if(p_v[j] == 0){
                    HamingDist +=1;
                } else if(p_v[j] > 1) {
                    if (edges[p_v[j]][1].capacity == 0){
                        vertices[p_v[j]].children.push_back(1);
                    }
                    ++edges[p_v[j]][1].capacity;
                }
            } else {
                if(p_v[j] == 0) {
                    if (edges[0][s_v[i]].capacity == 0){
                        vertices[0].children.push_back(s_v[i]);
                    }
                    ++edges[0][s_v[i]].capacity;
                } else if(p_v[j] == 1) {
                    if (edges[s_v[i]][1].capacity == 0){
                        vertices[s_v[i]].children.push_back(1);
                    }
                    ++edges[s_v[i]][1].capacity;
                } else {
                    if (edges[p_v[j]][s_v[i]].capacity == 0){
                        vertices[s_v[i]].children.push_back(p_v[j]);
                        vertices[p_v[j]].children.push_back(s_v[i]);
                    }
                    ++edges[p_v[j]][s_v[i]].capacity;
                    ++edges[s_v[i]][p_v[j]].capacity;
                }
            }
        }
    }
    return  HamingDist;
}

void print(vector<int>& v, vector<int>& dist_from_start){
    for(int i = 0; i < v.size(); ++i){
        if (v[i] > 1){
            if(dist_from_start[v[i]] == 100000000){
                v[i] = 1;
            } else {
                v[i] = 0;
            }
        }
        cout << v[i];
    }
}

int main(){
    string p = "", s = "";//строка и шаблон
    cin >> p >> s;
    int n = 1;
    vector<int> p_v;
    for(char i: p) {
        if (i == '0') {
            p_v.push_back(0);
        } else if (i == '1') {
            p_v.push_back(1);
        } else {
            p_v.push_back(++n);
        }
    }
    vector<int> s_v;
    for(char i: s) {
        if (i == '0') {
            s_v.push_back(0);
        } else if (i == '1') {
            s_v.push_back(1);
        } else {
            s_v.push_back(++n);
        }
    }
    vector<vector<edge>> edges(n+1, vector<edge>(n+1, edge(0)));
    vector<vert> vertices(n+1, vert());
    int HamingDist = build_graph(s_v, p_v, edges, vertices);
    HamingDist += Dinic(edges, vertices);
    vector<int> dist_from_start(n+1, 100000000);
    find_achievable(dist_from_start, edges, vertices);
    cout << HamingDist << endl;
    print(p_v, dist_from_start);
    cout << endl;
    print(s_v, dist_from_start);
    return 0;
}
