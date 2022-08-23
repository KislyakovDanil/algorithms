#include <iostream>
#include <vector>
using namespace std;

struct Interval {//период пребывания покупателя в магазине
    Interval(int x = 0, int y = 0) :x(x), y(y) {}
    int x;
    int y;
};

struct comparator{//сравнение по времени выхода
    bool operator()(Interval a, Interval b){
        return (a.y > b.y);
    };
};

template<class Iterator, class Comparator>
void SiftDown (Iterator i, Iterator begin, Iterator end, Comparator cmp) {
    Iterator left = i + distance(begin, i) + 1;
    Iterator right = i + distance(begin, i) + 2;
    Iterator max = i;
    if (left < end && cmp(*left, *max)) {
        max = left;
    }
    if (right < end && cmp(*right, *max)) {
        max = right;
    }
    if( max != i ) {
        swap( *i, *max );
        SiftDown( max, begin, end, cmp );
    }


}
/*template<class Iterator, class Comparator>
void SiftDown (Iterator i, Iterator begin, Iterator end, Comparator cmp) {
    Iterator left;
    Iterator right;
    Iterator max = i;
    do{
        i = max;
        left = i + distance(begin, i) + 1;
        right = i + distance(begin, i) + 2;
        if (right < end && cmp(*right, *max)) {
            max = right;
        }
        if (left < end && cmp(*left, *max)) {
            max = left;
        }
        swap(*i, *max);
    }while (!cmp(*max,*i));
}*/

template<class Iterator, class Comparator>
void BuildHeap( Iterator begin, Iterator end, Comparator cmp ) {
    for( auto i = begin + distance(begin,end)/2 - 1; i >= begin; --i ) {
        SiftDown(i, begin, end, cmp);
    }
}

template<class Iterator, class Comparator>// пирамидальная сортировка
void HeapSort( Iterator begin, Iterator end, Comparator cmp ) {
    BuildHeap( begin, end, cmp);
    while( begin < end ) {
        --end;
        swap( *begin, *end );
        SiftDown(begin, begin, end, cmp);
    }
}

int main() {
    size_t n;
    cin >> n;
    vector<Interval> A(n);
    for(auto i = A.begin(); i < A.end(); ++i){
        int x,y;
        cin >> x >> y;
        Interval In(x,y);
        *i = In;
    }
    comparator cmp;
    HeapSort( A.begin(), A.end(), cmp);
    int count = 0;
    int last = (A.end()-1)->y + 10;
    int prelast = (A.end()-1)->y + 10;//запоминаем время показа предыдущих реклам
    for (auto i = A.begin(); i < A.end(); ++i){
        int breaker = 0;
        if (last >= i->x &&  last <= i->y){
            ++breaker;
        }
        if (prelast >= i->x &&  prelast <= i->y){
            ++breaker;
        }
        if (breaker < 2) {
            count = count + 2 - breaker;
            if (breaker == 0){
                last = i->y;
                prelast = i->y - 1;
            } else if (last == i->y) {
                prelast = i->y - 1;
            } else {
                prelast = last;
                last = i->y;
            }
        }
    }
    cout << count;
    return 0;
}