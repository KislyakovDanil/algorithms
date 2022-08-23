#include <iostream>
using namespace std;

class Heap {
    public:
        Heap(int size);
        ~Heap();
        void heapify(int i);
        int getminsum();
        void BuildHeap(int* InputArr, int n);
    private:
        int* array;
        int HeapSize;
};

Heap :: Heap(int size) {
    HeapSize = size;
    array = new int[HeapSize];
}

Heap :: ~Heap() {
    delete[] array;
}

void Heap :: BuildHeap(int* InputArr, int n) {
    for (int i = 0; i < n; ++i) {
        array[i] = InputArr[i];
        int j = i;
        while (j > 0) {
            if (array[j] < array[(j-1)/2]) {
                swap(array[j], array[(j-1)/2]);
            }
            j = (j-1)/2;
        }
    }
}

void Heap:: heapify(int i) {
    int left, right;
    left = 2 * i + 1;
    right = 2 * i + 2;
    if (right < HeapSize && array[i] > array[right]) {
        swap(array[i], array[right]);
        heapify(right);
    }
    if (left < HeapSize && array[i] > array[left]) {
        swap(array[i], array[left]);
        heapify(left);
    }
}

int Heap:: getminsum() {
    if (array[2] < array[1] && HeapSize > 2) {
        swap(array[2], array[1]);
    }
    int x;
    x = array[0] + array[1];
    array[1] = array[0] + array[1];
    heapify(1);
    array[0] = array[HeapSize-1];
    HeapSize--;
    heapify(0);
    return(x);
}

int main() {
    int n = 0;
    cin >> n;
    int InputArr[n];
    for (int i = 0; i < n; ++i) {
        cin >> InputArr[i];
    }
    Heap HeapOne(n);
    HeapOne.BuildHeap(InputArr, n);
    HeapOne.heapify(0);
    int count = 0;
    for (int i = 0; i < n - 1; ++i) {
        count += HeapOne.getminsum();
    }
    cout << count;
    return(0);
}