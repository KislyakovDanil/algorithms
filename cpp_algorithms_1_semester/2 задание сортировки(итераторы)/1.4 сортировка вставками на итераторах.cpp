#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class comparator{//оператор сравнения
public:
    comparator(){}
    bool operator()(string a,string b){
        return a>b;
    };
};

template<class Iterator, class Comparator>
void insertionSort(Iterator begin, Iterator end, Comparator cmp) {
    // Инвариант: на полуинтервале [begin, sortedEnd) последовательность уже
    // отсортирована.
    //
    // std::next делает копию итератора, сдвинутую на 1 вперёд.
    // это отличается от ++ тем, что ++ меняет исходный итератор, а это — нет.
    // std::prev аналогично двигает копию назад.

    for (Iterator sortedEnd = std::next(begin); sortedEnd != end; ++sortedEnd) {
        // Нужно найти место для вставки *sortedEnd в полуинтервал [begin,
        // sortedEnd) Хотим получить итератор на место, _на которое_ нужно будет
        // переставить *sortedEnd. Это отличается от варианта с лекции: там
        // искалось место, _после которого_ ставился новый элемент.
        Iterator insertPosition = begin;
        while (insertPosition != sortedEnd && cmp(*insertPosition, *sortedEnd)) {
            ++insertPosition;
        }

        // hint: так как последовательность сортированная, ровно то же самое
        // можно было получить стандартной функцией бинарного поиска, которую
        // тоже можно использовать:
        // insertPosition = std::lower_bound(begin, sortedEnd, *sortedEnd, cmp);

        // Теперь хотим сдвинуть полуинтервал [insertPosition, sortedEnd) на
        // одну позицию вправо, чтобы поставить в insertPosition старое
        // значение *sortedEnd. Например, это можно сделать так:
        typename std::iterator_traits<Iterator>::value_type insertValue = *sortedEnd;
        for (Iterator it = sortedEnd; it != insertPosition; --it) {
            *it = *std::prev(it);
        }
        *insertPosition = insertValue;

        // hint: то, что сейчас произошло — это циклический сдвиг полуинтервала
        // [insertPosition, std::next(sortedEnd)) на одну позицию право. Для
        // этого есть стандартная функция, которую тоже можно было использовать:
        // std::rotate(insertPosition, sortedEnd, std::next(sortedEnd));
    }
}

int main(){
    int n;
    cin >> n;
    vector<string> A(n);
    for (auto i = A.begin(); i != A.end(); ++i){
        string str;
        cin >> str;
        *i = str;
    }
    comparator cmp;//объявляем чтобы подать
    insertionSort(A.begin(),A.end(), cmp);
    reverse(A.begin(),A.end());//переворачиваем т.к. упорядочили в обратном порядке
    for (auto i = A.begin(); i != A.end(); ++i){
        cout << *i << endl;
    }
}