#include <iostream>
using namespace std;

struct TreapNode {// элемент декартова дерева
    int key;
    int priority;
    TreapNode* left;
    TreapNode* right;
    TreapNode(int ThisKey, int ThisPriority){
        key = ThisKey;
        priority = ThisPriority;
        left = nullptr;
        right = nullptr;
    }
};

struct NaiveNode {// элемент наивного дерева
    int key;
    NaiveNode* left;
    NaiveNode* right;
    NaiveNode(int value){
        key = value;
        left = nullptr;
        right = nullptr;
    }
};

void split(TreapNode* node, TreapNode*& left, TreapNode*& right, int key) {// разрезание
    if (node == nullptr) {
        left = nullptr;
        right = nullptr;
        return;
    } else if (node->key < key) {
        split(node->right, node->right, right, key);
        left = node;
    } else {
        split(node->left, left, node->left, key);
        right = node;
    }
}

void Insert(TreapNode*& root, int key, int priority) {//декартова вставка
    if(root == nullptr) {
        root = new TreapNode(key, priority);
        return;
    }
    if(root->priority < priority) {
        TreapNode* newNode = new TreapNode(key, priority);
        TreapNode* right = nullptr;
        TreapNode* left = nullptr;
        split(root, left, right, key);
        newNode->right = right;
        newNode->left = left;
        root = newNode;
        return;
    } else if(key > root->key){
        Insert(root->right, key, priority);
    } else {
        Insert(root->left, key, priority);
    }
}

void NaiveInsert( NaiveNode*& node, int value )// наивная вставка
{
    if( node == nullptr ) {
        node = new NaiveNode( value );
        return;
    }
    if( node->key > value )
        NaiveInsert( node->left, value );
    else
        NaiveInsert( node->right, value );

}

template<class T>
void Clear( T* node ){// удаление
    if( node == nullptr )
        return;
    Clear( node->left );
    Clear( node->right );
    delete node;
}

template<class T>
int Count(T* root) {
    if (root != nullptr) {
        return 1 + max(Count(root->right), Count(root->left));
    } else {
        return 0;
    }
}

int main() {
    TreapNode* Root = nullptr;
    NaiveNode* NRoot = nullptr;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int Key;
        int Priority;
        cin >> Key;
        cin >> Priority;
        Insert(Root, Key, Priority);
        NaiveInsert(NRoot, Key);
    }
    cout << abs(Count(Root) - Count(NRoot));
    Clear(Root);
    Clear(NRoot);
    return 0;
}