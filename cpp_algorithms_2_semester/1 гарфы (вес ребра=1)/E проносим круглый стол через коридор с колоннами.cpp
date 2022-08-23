#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
using namespace std;


struct point{
    double x;
    double y;
    point(int first, int second):x(first), y(second){};
};

bool TableCan(double TD, vector<vector<double>>& edges){
    queue<int> q;
    q.push(edges.size() - 2);
    vector<bool> IsVisiting(edges.size(), false);
    IsVisiting[edges.size() - 2] = true;
    do{
        if (q.empty()){
            return true;
        }
        int v = q.front();
        q.pop();
        for (int i = 0; i < edges.size(); ++i){
            if(IsVisiting[i] == false && edges[v][i] <= TD){
                q.push(i);
                IsVisiting[i] = true;
            }
        }
    } while (IsVisiting[edges.size() - 1] == false);
    return false;
}

int main() {
    int XL = 0, XR = 0, N = 0;
    double R = 0;//координаты стен, радиус и число колон
    cin >> XL >> XR >> R >> N;
    vector<point> pillars;
    for (int i = 0; i < N; ++i){
        int x;
        int y;
        cin >> x >> y;
        point p = point(x,y);
        pillars.push_back(p);
    }
    vector<vector<double>> edges(N+2, vector<double>(N+2, 0));// N - левая стена, N+1 -правая
    for(int i = 0; i < N; ++i){//для всех колонн
        for(int j = 0; j < N; ++j){// запомнить расстояние до всех других(-2R)
            edges[i][j] = sqrt(pow((pillars[i].x - pillars[j].x),2) + pow((pillars[i].y - pillars[j].y),2)) - 2*R;
        }
        edges[i][N] = pillars[i].x - XL - R;// и до стен
        edges[N][i] = edges[i][N];
        edges[i][N+1] = XR - pillars[i].x - R;
        edges[N+1][i] = edges[i][N+1];
    }
    edges[N][N+1] = XR - XL;
    edges[N+1][N] = edges[N][N+1];

    //бинпоиск по размеру стола
    double left = 0;
    double right = XR - XL;
    double TD = (left+right)/2;
    while (right - left > 0.00001) {
        if (TableCan(TD, edges)) {
            left = TD;
        } else {
            right = TD;
        }
        TD = (left+right)/2;
    }

    cout <<  setprecision(3) << fixed << TD;
    return 0;
}