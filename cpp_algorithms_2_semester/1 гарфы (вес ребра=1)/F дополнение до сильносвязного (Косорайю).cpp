#include <iostream>
#include <vector>
using namespace std;

void Ordering(int v, vector<bool>& IsVisited, const vector<vector<int>>& edges, vector<int>& order) {//�������������� �� ������� ������ �� dfs
    IsVisited[v] = true;
    for (int i=0; i < edges[v].size(); ++i) {
        if (!IsVisited[edges[v][i]]) {
            Ordering(edges[v][i], IsVisited, edges, order);
        }
    }
    order.push_back (v);
}

void SearchConCom(int v, vector<bool>& IsVisited, const vector<vector<int>>& trans_edges, vector<int>& ConComs, int count) {//����� 1 ���
    ConComs[v] = count;
    IsVisited[v] = true;
    for (int i : trans_edges[v]) {
        if (!IsVisited[i]) {
            SearchConCom(i, IsVisited, trans_edges, ConComs, count);
        }
    }
}

void Kosaraiy(const vector<vector<int>>& edges, const vector<vector<int>>& trans_edges, vector<int>& ConComs, int& count){
    vector<bool> IsVisited(edges.size(), false);
    vector<int> order;// ������� � ������� ���������� ������� ������ (�������������� ����������)
    for (int i = 1; i < edges.size(); ++i) {//�� ��������� 0
        if (!IsVisited[i]) {
            Ordering(i, IsVisited, edges, order);
        }
    }
    fill(IsVisited.begin(), IsVisited.end(), false);
    for (int i = 0; i < order.size(); ++i){
        int v = order[order.size()-1-i];
        if (!IsVisited[v]) {
            SearchConCom(v, IsVisited, trans_edges, ConComs, count);
            count += 1;
        }
    }
}

int main(){
    int v, e;
    cin >> v >> e;
    vector<vector<int>> edges(v+1);//v+1 �.�.� ������� ����� � 1
    vector<vector<int>> trans_edges(v+1);
    for (int i = 0; i < e; ++i){
        int from;
        int to;
        cin >> from >> to;
        edges[from].push_back(to);
        trans_edges[to].push_back(from);
    }
    vector<int> ConComs(edges.size(), 0); //�������������� � ���
    int count = 0; // � ��������� ��� (�� ������� ������� ���������� ���)
    Kosaraiy(edges, trans_edges, ConComs, count);
    vector<bool> Sources(count, true);
    vector<bool> Sinks(count, true);
    for (int i = 0; i < ConComs.size(); ++i){//��� ���� ���������
        for (int j = 0; j < edges[i].size(); ++j) {//��� ���� ��������� ����
            if (ConComs[i] != ConComs[edges[i][j]]) {
                Sinks[ConComs[i]] = false;
                Sources[ConComs[edges[i][j]]] = false;
            }
        }
    }
    bool IsOneKSS = true;//�������� �� �������������� ���
    for (int i: ConComs) {
        if (i > 0) {
            IsOneKSS = false;
        }
    }
    int numSources = 0;
    int numSinks = 0;
    for (int i = 0; i < count; ++i){
        if(Sources[i]){
            numSources += 1;
        }
        if(Sinks[i]){
            numSinks += 1;
        }
    }
    if (IsOneKSS){
        cout << 0;
    } else {
        cout << max(numSources, numSinks);
    }
}