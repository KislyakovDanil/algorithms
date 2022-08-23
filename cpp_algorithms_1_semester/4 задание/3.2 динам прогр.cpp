#include <iostream>
#include <vector>
using namespace std;

uint64_t FindNumberSplitting(uint64_t n ){
    vector<vector<uint64_t>> NumSplitting(n + 1);
    for (uint64_t i = 0; i < n + 1; ++i ){//��������� ��������
        NumSplitting[i].resize(n + 1, 0);
        NumSplitting[0][i] = 0;//�������� ��������� �� 0
        NumSplitting[i][0] = 1;//�������� ��������� 0         (0,0)=1
    }
    for ( uint64_t i = 1; i < n + 1; ++i ){//������������ ����� � ����������
        for (uint64_t j = 1; j < n + 1; ++j ){//�������������� �����
            if (i > j){
                NumSplitting[i][j] = NumSplitting[i - 1][j];
            } else {
                NumSplitting[i][j] = NumSplitting[i - 1][j] + NumSplitting[i - 1][j - i];
            }
        }
    }
    return NumSplitting[n][n];
}

int main() {
    //����: ����������� ����� ������� -- ��� ����������� ��������� ��� ���������� ����� n
    // (n; 1,...,k) = (n-k; 1,...,k-1) + (n; 1,...,k-1) (���� ��� ��� ����� k � ���������)
    uint64_t n;
    cin >> n;
    cout << FindNumberSplitting(n);
}