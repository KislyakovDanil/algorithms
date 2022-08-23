#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void cycle_step(queue<int> &VerS,vector<vector<int>> &graph, vector<int> &IsVisiting, vector<int>  &Counts){
    int N = VerS.size();
    for (int i = 0; i < N; ++i){
        int v = VerS.front();
        VerS.pop();
        for (int j = 0; j < graph[v].size(); ++j) {
            if (IsVisiting[graph[v][j]] == 0 || IsVisiting[graph[v][j]] > IsVisiting[v]) {
                if (IsVisiting[graph[v][j]] == 0 ) {
                    VerS.push(graph[v][j]);
                    IsVisiting[graph[v][j]] = IsVisiting[v] + 1;
                }
                Counts[graph[v][j]] += Counts[v];
            }
        }
    }
}

int way_num(int startVal, int finishVal, vector<vector<int>> &graph){
    queue<int> VerS;
    VerS.push(startVal);
    vector<int>  IsVisiting(graph.size(),0);// 0 - не посещали, иначе - номер слоя
    vector<int>  Counts(graph.size(),0);
    IsVisiting[startVal] = 1;
    Counts[startVal] = 1;
    bool stap = true;
    do{
        if(stap){
            cycle_step(VerS, graph, IsVisiting, Counts);
            stap = false;
        } else {
            cycle_step(VerS, graph, IsVisiting, Counts);
            stap = true;
        }
    } while (!VerS.empty() && IsVisiting[finishVal] == 0);
    return Counts[finishVal];
}

int main() {
    int v = 0;
    int n = 0;
    cin >> v >> n;
    vector<vector<int>> graph(v);
    for (int i = 0; i < n; ++i){
        int v1, v2;
        cin >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
    int startVal;
    int finishVal;
    cin >> startVal >> finishVal;
    if (startVal == finishVal){
        cout << 1;
    } else {
        cout << way_num(startVal, finishVal, graph);
    }
    return 0;
}