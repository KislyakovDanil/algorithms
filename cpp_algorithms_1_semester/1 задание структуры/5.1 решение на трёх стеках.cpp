#include <iostream>
using namespace std;

class Stack {
    public:
        Stack(int size);
        ~Stack();
        void PushFront(char a);
        void DelFront();
        char viewFront();
        void UpArray();
        void overturning();//переворачивание
    private:
        char* array;
        int arraySize;
        int head;//индекс свободной ячейки
};

Stack::Stack(int size) {
    head = 0;
    arraySize = size;
    array = new char[arraySize];
    PushFront(' ');
}

Stack::~Stack() {
    delete[] array;
}

void Stack::PushFront(char a) { // добавление нового элемента
    if (head == arraySize) {
        UpArray();
    }
    array[head] = a;
    head = head + 1;
}

char Stack::viewFront() { // просмотр крайнего элемента
    return array[head - 1];
}

void Stack::DelFront() { // удаление крайнего элемента
    head = head - 1;
}

void Stack::UpArray() { // удвоение размера стека
    int newArraySize = arraySize * 2;
    char* newArray = new char[newArraySize];
    for (int i = 0; i < head; ++i) {
            newArray[i] = array[i];
    }
    delete[] array;
    arraySize = newArraySize; // обновляем характеристики массива
    array = newArray;
}

void Stack::overturning() { //переворачивание стека
    int newArraySize = arraySize;
    char* newArray = new char[newArraySize];
    newArray[0] = array[0];//сохраниение пустого элемента ' ' на самом дне стека
    for (int i = 1; i < head; ++i) {
            newArray[i] = array[head-i];
    }
    delete[] array;
    arraySize = newArraySize;
    array = newArray;
}

int main() {
    Stack BackBeginStack(2); //запись недостающих в начале элементов(Back лишний, убери)
    Stack EndStack(2); //недостающие в конце элементы
    Stack BackMainStack(2); //перевёрнутая запись центральных элементов
    bool possible = true;//возможность построить последовательность
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); ++i){
        char a = s[i];
        char b;
        switch(a){
            case'}':
                b = '{';
            break;
            case')':
                b = '(';
            break;
            case']':
                b = '[';
            break;
            case'[':
                b = ']';
            break;
            case'{':
                b = '}';
            break;
            case'(':
                b = ')';
            break;
        };
        switch(a){
            case'}':
            case')':
            case']':
                if (a == EndStack.viewFront()) {
                    EndStack.DelFront();
                    BackMainStack.PushFront(a);
                } else if (EndStack.viewFront() == ' '){
                    BackMainStack.PushFront(a);
                    BackBeginStack.PushFront(b);
                } else {
                    possible = false;
                }
            break;
            case'[':
            case'{':
            case'(':
                EndStack.PushFront(b);
                BackMainStack.PushFront(a);
            break;
        }
    };
    BackMainStack.overturning();
    if (possible == false){
        cout << "IMPOSSIBLE";
    } else {
        while( BackBeginStack.viewFront() !=' '){
            char a = BackBeginStack.viewFront();
            cout << a;
            BackBeginStack.DelFront();
        }
        while( BackMainStack.viewFront() !=' '){
            char a = BackMainStack.viewFront();
            cout << a;
            BackMainStack.DelFront();
        }
        while( EndStack.viewFront() !=' '){
            char a = EndStack.viewFront();
            cout << a;
            EndStack.DelFront();
        }
    }
    return(0);
}