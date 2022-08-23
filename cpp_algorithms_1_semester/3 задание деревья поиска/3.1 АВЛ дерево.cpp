#include <iostream>

using namespace std;

struct AVLnode { // ������� ��� ������
    int key;
    AVLnode *left;
    AVLnode *right;
    int height; // ������ ������
    int number = 0; // ����� ��������� � ���������
    AVLnode(int k): key(k), left(nullptr), right(nullptr), height (1), number (1) {
    }
};

void Refresh(AVLnode *&p) {//��������� ������ � ����� ���� � ���������
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

int HeightDiff(AVLnode *p) {//������� ����� �����������
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

void rotateright(AVLnode *&p) { // ������ ������� ������ p
    AVLnode *q = p->left;
    p->left = q->right;
    q->right = p;
    p = q;
    Refresh(p->right);
    Refresh(p);
}

void rotateleft(AVLnode *&p) { // ����� ������� ������ q
    AVLnode *q = p->right;
    p->right = q->left;
    q->left = p;
    p = q;
    Refresh(p->left);
    Refresh(p);
}

void balance(AVLnode *&p) { // ������������ ���� p
    Refresh(p);
    if (HeightDiff(p) == 2) {// �����
        if (HeightDiff(p->right) < 0) {// �������
            rotateright(p->right);
        }
        rotateleft(p);
    } else if (HeightDiff(p) == -2) {// ������
        if (HeightDiff(p->left) > 0) {// �������
            rotateleft(p->left);
        }
        rotateright(p);
    }
}

int insert(AVLnode *&p,
           int k) { // ������� ����� k � ������ � ������ p; ���������� �� ����� ����� ��������� ����������� ����
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
    //"���������" ����� �� ����������� ������� � �����. ��������� � ������ ������� ������������������.
}

AVLnode *removeMin(AVLnode *&node, AVLnode *&min) { //���������� ������ ��� min
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
void Clear(T *node) {// ��������
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