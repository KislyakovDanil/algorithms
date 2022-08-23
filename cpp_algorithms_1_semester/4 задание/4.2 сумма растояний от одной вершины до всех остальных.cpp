#include <iostream>
#include <vector>
using namespace std;

struct Node{
    Node(int p = -1) :parent(p)  {}
    int NumNodeInSubtree = 1;//число элементов в поддереве
    vector<int> Sons;//позиции сыновей
    int parent;//позиция родителя
    uint64_t SumEdgeDistance = 0;//сумма расстояний до всех остальных вершин
};

void InputTree(vector<Node>& Tree, int n){//вводим дерево
    Tree[0] = (-1);
    for(int i = 1; i < n; ++i){
        int node1;
        int node2;
        cin >> node1 >> node2;
        if (node1 > node2){
            Tree[node1] = (node2);
            Tree[node2].Sons.push_back(node1);
        } else {
            Tree[node2] = (node1);
            Tree[node1].Sons.push_back(node2);
        }
    }
}

void ColcSumEdgeDistance(vector<Node>& Tree, int n){
    for (int i = n - 1; i > 0; --i){//считаем колличество элементов в поддеревьях, 0 -- корень
        Tree[Tree[i].parent].NumNodeInSubtree += Tree[i].NumNodeInSubtree;
        Tree[0].SumEdgeDistance += Tree[i].NumNodeInSubtree;//параллельно считаем сумму расстояний от вершин до корня
    }
    cout << Tree[0].SumEdgeDistance << " ";
    for (int i = 1; i < n; ++i){
        Tree[i].SumEdgeDistance = Tree[Tree[i].parent].SumEdgeDistance - 2*Tree[i].NumNodeInSubtree + n; //теперь считаем для остальных
        cout << Tree[i].SumEdgeDistance << " ";//(k элементов стало ближе, а n-k дальше)
    }

}

int main() {
    int n;
    cin >> n;
    vector<Node> Tree(n);
    InputTree(Tree,n);//ввод
    ColcSumEdgeDistance(Tree,n);//основная функция
    return 0;
}