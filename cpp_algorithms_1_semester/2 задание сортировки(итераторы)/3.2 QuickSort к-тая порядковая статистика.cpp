#include <iostream>
#include <vector>
using namespace std;

template<class Iterator>
Iterator Pivot(Iterator begin, Iterator end) {//опорный элемент сортировкой трёх
    Iterator medium = begin + distance(begin, end)/2;
    if( *begin <= *medium ) {
        if( *medium <= *end ) {
            return medium;
        } else {
            if( *begin <= *end )
                return end;
                    else
                return begin;
        }
    } else {
        if( *medium <= *end ) {
            if( *begin <= *end )
                return begin;
                    else
            return end;
        } else {
            return medium;
        }
    }
}




template<class Iterator>
Iterator Partition(Iterator begin, Iterator end) {//переброска относительно опорного
    Iterator piv = Pivot (begin, end - 1);
    swap(*begin, *piv);
    Iterator i = end - 1;
    Iterator j = end - 1;
    while (j > begin){
        if (*begin >= *j){
            --j;
        } else {
            swap(*i,*j);
            --i;
            --j;
        }
    }
    swap(*i, *begin);
    return i;
}

template <class Iterator>
int kStat( Iterator begin, Iterator end, size_t k) {//поиск к-той порядковой статистики
    Iterator i = Partition(begin, end);
    Iterator begin1 = begin;
    while (distance(begin1, i)!= k) {
        if (distance(begin1, i) > k){
            end = i;
            i = Partition (begin, i);
        } else {
            begin = i + 1;
            i = Partition (i + 1, end);
        }
    }
    return *i;
}

int main()
{
    size_t n;
    cin >> n;
    size_t k;
    cin >> k;
    vector<int>A(n);
    for(auto i = A.begin(); i < A.end(); ++i) {
        cin >> *i;
    }
    int Stat = kStat(A.begin(),A.end(), k);
    cout << Stat;
    return 0;
}