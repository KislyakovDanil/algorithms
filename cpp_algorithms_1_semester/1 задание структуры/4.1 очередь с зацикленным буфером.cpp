#include <iostream>
using namespace std;

class Queue {
    public:
        Queue(int size);
        ~Queue();
        void PushBack(int a);
        int PopFront();
        void UpBuffer();
    private:
        int* buffer;
        int bufferSize;
        int head;
        int tail;
};

Queue::Queue(int size) {
    head = 0;
    tail = 0;
    bufferSize = size;
    buffer = new int[bufferSize];
}

Queue::~Queue() {
    delete[] buffer;
}

void Queue::PushBack(int a) { // ����������
    if ((tail + 1 == head) || (tail == bufferSize - 1 && head == 0)) {
        UpBuffer();
    }
    buffer[tail] = a;
    if (tail + 1 == bufferSize) {
        tail = 0;
    } else {
        tail = tail + 1;
    }
}

int Queue::PopFront() { // ����������
    int Pop = buffer[head];
    if (head == tail) {
        Pop = -1;
    }
    if (head != tail) {
        if (head + 1 == bufferSize) {
            head = 0;
        } else {
         head = head + 1;
        }
    }
    return Pop;
}

void Queue::UpBuffer() { // ���������� ������
    int newBufferSize = bufferSize * 2;
    int* newBuffer = new int[newBufferSize];
    if ( tail > head ) { //����� 1 ������: tail == buffersize - 1 && head == 0
        for (int i = 0; i < bufferSize ; ++i) {
            newBuffer[i] = buffer[i];
        }
    } else { // ���� ������ ����������� ����� �����-������ �������
        for (int i = head; i < bufferSize; ++i) {
            newBuffer[i - head] = buffer[i];
        }
        for (int i = 0; i < head; ++i) {
            newBuffer[bufferSize - head + i] = buffer[i];
        }
    }
    delete[] buffer;
    head = 0; // ��������� �������������� �������
    tail = bufferSize - 1;
    bufferSize = newBufferSize;
    buffer = newBuffer;
}

int main() {
    int h = 2;
    Queue QueueOne(h);
    int n = 0;
    cin >> n;
    string Str ="YES";
    for (int i = 0; i < n; ++i) {
        int a = 0;
        int b = 0;
        cin >> a >> b;
        if (a == 2) {
            if (b != QueueOne.PopFront()) {
                Str = "NO";
            }
        } else {
            QueueOne.PushBack(b);
        }
    }
    cout << Str;
    return(0);
}