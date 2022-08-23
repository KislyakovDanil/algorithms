#include <iostream>
#include <vector>
using namespace std;

template <class T>
int GetByte(T x, int Nbyte){
    return x>>(8*Nbyte) & ((1<<8)-1);
}

template <class Iterator>
void CountingSort(Iterator  begin, Iterator  end, int byte) {
    vector<int>B(distance(begin,end));
    for(auto i = B.begin(); i < B.end(); ++i ){//��������� ����� �����
        *i = GetByte(*(begin + distance(B.begin(),i)),byte);
    }
    vector<int>C(256);//������� �������� ������
    for(auto i = C.begin(); i < C.end(); ++i ){
        *i = 0;
    }
    for(auto i = B.begin(); i < B.end(); ++i){
        ++C[*i];
    }
    int sum = 0;
    for( auto i = C.begin(); i < C.end(); ++i ) {// ������ �����.(�[i]-������� ������� ����������� � ����������� ���������� � ������������ �������)
        int tmp = *i;
        *i = sum;
        sum += tmp;
    }
    vector<long long int>D(distance(begin,end));//���������������� A
    for( auto i = B.begin(); i < B.end(); ++i ) {
        D[C[*i]++] = *(begin + distance(B.begin(), i));//��������� �������� � ������������ � �� �������� ���������
    }// � ��������������� �� ����������, ������� ������� �������� � (������� ����������� ������� �����)
    for(auto i = begin; i < end; ++i ){
        *i = *(D.begin() + distance(begin,i));//�������� ������ � �����������
    }
}

template <class Iterator>
void LSDSort (Iterator  begin, Iterator  end) {
    for (int r = 0; r < sizeof(long long); ++r){
        CountingSort( begin, end, r);
    }
}

int main()
{
    size_t n;
    cin >> n;
    vector<long long int>A(n);
    for(auto i = A.begin(); i < A.end(); ++i) {
        cin >> *i;
    }
    LSDSort( A.begin(), A.end());
    for(auto i = A.begin(); i < A.end(); ++i) {
        cout << *i << " ";
    }
}