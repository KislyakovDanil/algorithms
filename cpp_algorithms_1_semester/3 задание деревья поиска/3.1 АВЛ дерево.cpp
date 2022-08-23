#include <iostream>

using namespace std;

struct AVLnode { // элемент АВЛ дерева
    int key;
    AVLnode *left;
    AVLnode *right;
    int height; // высота дерева
    int number = 0; // число элементов в поддереве
    AVLnode(int k): key(k), left(nullptr), right(nullptr), height (1), number (1) {
    }
};

void Refresh(AVLnode *&p) {//обновляет высоту и число элем в поддереве
    if (!p) {
        return;
    }
    int LeftH = 0;
    int RightH = 0;
    int LeftN = 0;
    int RightN = 0;
    if (p->left) {
        LeftN = (p->left)->number;
        LeftH = (p->left)->height;
    }
    if (p->right) {
        RightN = (p->right)->number;
        RightH = (p->right)->height;
    }
    p->number = LeftN + RightN + 1;
    p->height = max(LeftH, RightH) + 1;
}

int HeightDiff(AVLnode *p) {//разница высот поддеревьев
    int LeftH = 0;
    int RightH = 0;
    if (!p) {
        return 0;
    }
    if (p->left) {
        LeftH = (p->left)->height;
    }
    if (p->right) {
        RightH = (p->right)->height;
    }
    return RightH - LeftH;
}

void rotateright(AVLnode *&p) { // правый поворот вокруг p
    AVLnode *q = p->left;
    p->left = q->right;
    q->right = p;
    p = q;
    Refresh(p->right);
    Refresh(p);
}

void rotateleft(AVLnode *&p) { // левый поворот вокруг q
    AVLnode *q = p->right;
    p->right = q->left;
    q->left = p;
    p = q;
    Refresh(p->left);
    Refresh(p);
}

void balance(AVLnode *&p) { // балансировка узла p
    Refresh(p);
    if (HeightDiff(p) == 2) {// левый
        if (HeightDiff(p->right) < 0) {// большой
            rotateright(p->right);
        }
        rotateleft(p);
    } else if (HeightDiff(p) == -2) {// правый
        if (HeightDiff(p->left) > 0) {// большой
            rotateleft(p->left);
        }
        rotateright(p);
    }
}

int insert(AVLnode *&p,
           int k) { // вставка ключа k в дерево с корнем p; возвращает на каком месте находится вставляемый ключ
    if (!p) {
        p = new AVLnode(k);
        return 0;
    }
    int num = 0;
    if (k > p->key) {
        num = insert(p->right, k);
    } else {
        if (p->right) {
            num = (p->right)->number;
        }
        num += insert(p->left, k) + 1;
    }
    balance(p);
    return num;
    //"Отступаем" назад от добавленной вершины к корню. Проверяем в каждой вершине сбалансированность.
}

AVLnode *removeMin(AVLnode *&node, AVLnode *&min) { //возвращает дерево без min
    if (node->left == nullptr) {
        min = node;
        return node->right;
    }
    node->left = removeMin(node->left, min);
    balance(node);
    return node;
}

void remove(AVLnode *&p, int number) {
    if (!p) {
        return;
    }
    if (p->right && number < (p->right)->number) {
        remove(p->right, number);
    } else if (p->right && number > (p->right)->number) {
        remove(p->left, number - (p->right)->number - 1);
    } else {
        AVLnode *l = p->left;
        AVLnode *r = p->right;
        delete p;
        if (r == nullptr) {
            p = l;
            return;
        }
        AVLnode *min = nullptr;
        AVLnode *tmp = removeMin(r, min);
        min->right = tmp;
        min->left = l;
        p = min;
        Refresh(p);
    }
    balance(p);
}

template<class T>
void Clear(T *node) {// удаление
    if (!node) {
        return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
}

int main() {
    AVLnode *Root = nullptr;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int Command;
        int Key;
        cin >> Command;
        cin >> Key;
        if (Command == 1) {
            cout << insert(Root, Key) << " ";
        } else {
            remove(Root, Key);
        }
    }
    Clear(Root);
    return 0;//
}