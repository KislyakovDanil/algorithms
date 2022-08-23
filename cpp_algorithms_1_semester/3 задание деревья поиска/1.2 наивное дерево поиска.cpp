#include <iostream>
using namespace std;

struct CNode {//элемент дерева
    CNode* Left;
    CNode* Right;
    int key;
    CNode(int value){
        key = value;
        Left = nullptr;
        Right = nullptr;
    }
};

void Insert( CNode*& node, int value )//вставка
{
    if( node == nullptr ) {
        node = new CNode( value );
        return;
    }
    if( node->key > value )
        Insert( node->Left, value );
    else
        Insert( node->Right, value );

};

void Print( CNode* node )//распечатка
{
    if( node == nullptr )
        return;
    cout << node->key << " ";
    Print( node->Left );
    Print( node->Right );
};

void Del( CNode* node ){//удаление
    if( node == nullptr )
        return;
    Del( node->Left );
    Del( node->Right );
    delete node;
};

int main(){
    CNode* node = nullptr;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i){
        int key;
        cin >> key;
        Insert(node, key);
    }
    Print (node);
    Del (node);
    return 0;
}