#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int m;
    cin >> m;
    int A[n + 1];
    for (int i = 1; i < n + 1; ++i) {
        cin >> A[i];
    }
    int B[m];
    for (int j = 0; j < m; ++j) {
        cin >> B[j];
    }
    int i = 1;
    for (int j = 0; j < m; ++j) {
        do {
            i = i * 2;
        } while ( i < n &&  A[i] < B[j]);
        i = i / 2;
        int right = i * 2;
        if (right > n){
            right = n;
        }
        int left  = i;
        
        int mid = 0;
        do {
            mid = left + (right - left) / 2;
            
            if ( B[j] > A[mid] ) {
                left = mid + 1;
            } else {
                right = mid;
            }
        } while ( right > left );
        if ( A[left] == B[j] ) {
            cout << A[left];
            cout << " ";
        }
    }
    return 0;
}