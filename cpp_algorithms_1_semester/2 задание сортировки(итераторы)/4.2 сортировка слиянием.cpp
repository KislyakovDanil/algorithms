#include <iostream>
#include <vector>
using namespace std;


template<class Iterator>
void merge(Iterator beginA, Iterator endA, Iterator beginB, Iterator endB, vector<int> & c) { // ������� ��� �������
    Iterator i = beginA;
    Iterator j = beginB;
    Iterator g = c.begin();
    while(i < endA && j < endB){
        if(*i <= *j){
            *g = *i;
            ++i;
            ++g;
        } else {
            *g = *j;
            ++j;
            ++g;
        }
    }
    while(j <endB){
        *g = *j;
        ++j;
        ++g;
    }
    while(i < endA){
        *g = *i;
        ++i;
        ++g;
    }
}



template<class Iterator>
void mergeSort(Iterator left, Iterator right){
    if(left == right - 1){
        return;
    }
    Iterator mid = left + distance(left,right)/ 2;
    mergeSort(left, mid);
    mergeSort(mid, right);
    vector<int> c(distance(left, right));
    merge(left, mid, mid, right, c);
    for (auto i = left; i < right; ++i){
        *i = c[distance(left,i)];
    }
}




int main() {
    size_t n = 0;
    cin >> n;
    size_t k = 0;
    cin >> k;
    size_t number = n/k;//����� ����� ����������� ����� �
    vector<int>A(k);//������ ������ ����������
    for (auto i = A.begin(); i < A.end(); ++i){
        cin >> *i;
    }
    for (int j = 1; j < number; ++j){
        vector<int>B(k);//������ ��������� ����������
        for (auto i = B.begin(); i < B.end(); ++i){
            cin >> *i;
        }
        vector<int>C(2*k);//���������� 2 ����������
        for (auto i = C.begin(); i < C.begin()+k; ++i){
            *i= A[distance(C.begin(),i)];
        }
        for (auto i = C.begin()+k; i < C.end(); ++i){
            *i = B[distance(C.begin()+k,i)];
        }
        mergeSort(C.begin(), C.end());//������ ��
        for (auto i = C.begin(); i < C.begin()+k; ++i){
            cout << *i << " ";
        }//������� ������(������� ����)
        for (auto i = C.begin()+k; i < C.end(); ++i){
            A[distance(C.begin()+k,i)] = *i;
        }//����� -- ����� 1 ����������
    }
    vector<int>B(n-number*k);//�������
    for (auto i = B.begin(); i < B.end(); ++i){
        cin >> *i;
    }
    vector<int>C(k+n-number*k);//����������
    for (auto i = C.begin(); i < C.begin()+k; ++i){
        *i= A[distance(C.begin(),i)];
    }
    for (auto i = C.begin()+k; i < C.end(); ++i){
        *i = B[distance(C.begin()+k,i)];
    }
    mergeSort(C.begin(), C.end());//������ ��
    for (auto i = C.begin(); i < C.end(); ++i){
        cout << *i << " ";;
    }//�������
    return 0;
}