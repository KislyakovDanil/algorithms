#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class comparator{//�������� ���������
public:
    comparator(){}
    bool operator()(string a,string b){
        return a>b;
    };
};

template<class Iterator, class Comparator>
void insertionSort(Iterator begin, Iterator end, Comparator cmp) {
    // ���������: �� ������������� [begin, sortedEnd) ������������������ ���
    // �������������.
    //
    // std::next ������ ����� ���������, ��������� �� 1 �����.
    // ��� ���������� �� ++ ���, ��� ++ ������ �������� ��������, � ��� � ���.
    // std::prev ���������� ������� ����� �����.

    for (Iterator sortedEnd = std::next(begin); sortedEnd != end; ++sortedEnd) {
        // ����� ����� ����� ��� ������� *sortedEnd � ������������ [begin,
        // sortedEnd) ����� �������� �������� �� �����, _�� �������_ ����� �����
        // ����������� *sortedEnd. ��� ���������� �� �������� � ������: ���
        // �������� �����, _����� ��������_ �������� ����� �������.
        Iterator insertPosition = begin;
        while (insertPosition != sortedEnd && cmp(*insertPosition, *sortedEnd)) {
            ++insertPosition;
        }

        // hint: ��� ��� ������������������ �������������, ����� �� �� �����
        // ����� ���� �������� ����������� �������� ��������� ������, �������
        // ���� ����� ������������:
        // insertPosition = std::lower_bound(begin, sortedEnd, *sortedEnd, cmp);

        // ������ ����� �������� ������������ [insertPosition, sortedEnd) ��
        // ���� ������� ������, ����� ��������� � insertPosition ������
        // �������� *sortedEnd. ��������, ��� ����� ������� ���:
        typename std::iterator_traits<Iterator>::value_type insertValue = *sortedEnd;
        for (Iterator it = sortedEnd; it != insertPosition; --it) {
            *it = *std::prev(it);
        }
        *insertPosition = insertValue;

        // hint: ��, ��� ������ ��������� � ��� ����������� ����� �������������
        // [insertPosition, std::next(sortedEnd)) �� ���� ������� �����. ���
        // ����� ���� ����������� �������, ������� ���� ����� ���� ������������:
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
    comparator cmp;//��������� ����� ������
    insertionSort(A.begin(),A.end(), cmp);
    reverse(A.begin(),A.end());//�������������� �.�. ����������� � �������� �������
    for (auto i = A.begin(); i != A.end(); ++i){
        cout << *i << endl;
    }
}