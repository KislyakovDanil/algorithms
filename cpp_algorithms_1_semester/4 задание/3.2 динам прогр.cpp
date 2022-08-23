#include <iostream>
#include <vector>
using namespace std;

uint64_t FindNumberSplitting(uint64_t n ){
    vector<vector<uint64_t>> NumSplitting(n + 1);
    for (uint64_t i = 0; i < n + 1; ++i ){//начальные значения
        NumSplitting[i].resize(n + 1, 0);
        NumSplitting[0][i] = 0;//способов разложить на 0
        NumSplitting[i][0] = 1;//способов разложить 0         (0,0)=1
    }
    for ( uint64_t i = 1; i < n + 1; ++i ){//максимальное число в разложении
        for (uint64_t j = 1; j < n + 1; ++j ){//раскладываемое число
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
    //идея: колличество таких пирамид -- это колличество разбиений без повторений числа n
    // (n; 1,...,k) = (n-k; 1,...,k-1) + (n; 1,...,k-1) (было или нет число k в разбиении)
    uint64_t n;
    cin >> n;
    cout << FindNumberSplitting(n);
}