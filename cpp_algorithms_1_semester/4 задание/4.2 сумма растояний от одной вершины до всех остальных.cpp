#include <iostream>
#include <vector>
using namespace std;

struct Node{
    Node(int p = -1) :parent(p)  {}
    int NumNodeInSubtree = 1;//����� ��������� � ���������
    vector<int> Sons;//������� �������
    int parent;//������� ��������
    uint64_t SumEdgeDistance = 0;//����� ���������� �� ���� ��������� ������
};

void InputTree(vector<Node>& Tree, int n){//������ ������
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
    for (int i = n - 1; i > 0; --i){//������� ����������� ��������� � �����������, 0 -- ������
        Tree[Tree[i].parent].NumNodeInSubtree += Tree[i].NumNodeInSubtree;
        Tree[0].SumEdgeDistance += Tree[i].NumNodeInSubtree;//����������� ������� ����� ���������� �� ������ �� �����
    }
    cout << Tree[0].SumEdgeDistance << " ";
    for (int i = 1; i < n; ++i){
        Tree[i].SumEdgeDistance = Tree[Tree[i].parent].SumEdgeDistance - 2*Tree[i].NumNodeInSubtree + n; //������ ������� ��� ���������
        cout << Tree[i].SumEdgeDistance << " ";//(k ��������� ����� �����, � n-k ������)
    }

}

int main() {
    int n;
    cin >> n;
    vector<Node> Tree(n);
    InputTree(Tree,n);//����
    ColcSumEdgeDistance(Tree,n);//�������� �������
    return 0;
}