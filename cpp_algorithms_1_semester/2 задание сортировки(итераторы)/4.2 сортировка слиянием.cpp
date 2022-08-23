#include <iostream>
#include <vector>
using namespace std;


template<class Iterator>
void merge(Iterator beginA, Iterator endA, Iterator beginB, Iterator endB, vector<int> & c) { // сливаем два вектора
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
    size_t number = n/k;//число целых промежутков длины к
    vector<int>A(k);//читаем первый промежуток
    for (auto i = A.begin(); i < A.end(); ++i){
        cin >> *i;
    }
    for (int j = 1; j < number; ++j){
        vector<int>B(k);//читаем очередной промежуток
        for (auto i = B.begin(); i < B.end(); ++i){
            cin >> *i;
        }
        vector<int>C(2*k);//объединяем 2 промежутка
        for (auto i = C.begin(); i < C.begin()+k; ++i){
            *i= A[distance(C.begin(),i)];
        }
        for (auto i = C.begin()+k; i < C.end(); ++i){
            *i = B[distance(C.begin()+k,i)];
        }
        mergeSort(C.begin(), C.end());//сортим их
        for (auto i = C.begin(); i < C.begin()+k; ++i){
            cout << *i << " ";
        }//выводим начало(меньшие элем)
        for (auto i = C.begin()+k; i < C.end(); ++i){
            A[distance(C.begin()+k,i)] = *i;
        }//конец -- новый 1 промежуток
    }
    vector<int>B(n-number*k);//остаток
    for (auto i = B.begin(); i < B.end(); ++i){
        cin >> *i;
    }
    vector<int>C(k+n-number*k);//объединяем
    for (auto i = C.begin(); i < C.begin()+k; ++i){
        *i= A[distance(C.begin(),i)];
    }
    for (auto i = C.begin()+k; i < C.end(); ++i){
        *i = B[distance(C.begin()+k,i)];
    }
    mergeSort(C.begin(), C.end());//сортим их
    for (auto i = C.begin(); i < C.end(); ++i){
        cout << *i << " ";;
    }//выводим
    return 0;
}