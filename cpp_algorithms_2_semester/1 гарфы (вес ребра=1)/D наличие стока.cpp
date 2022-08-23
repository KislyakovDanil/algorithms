#include <iostream>
#include <vector>
using namespace std;

int main() {
    int v;
    cin >> v;
    vector<int> s(v);//очередная строка
    vector<bool> fromTop(v, true);//все ли в строке 0?
    vector<int> toTop(v, 1);//счётчики 1 в столбце(начинаем с 1, в итоге должно быть v)
    for (int i = 0; i < v; ++i){
        for (int j = 0; j < v; ++j){
            cin >> s[j];
            if (s[j] == 1){
                fromTop[i] = false;
                toTop[j] += 1;
            }
        }
    }
    bool sink = false;
    for (int i = 0; i < v; ++i){
        if ((fromTop[i] == true) && (toTop[i] == v)){
            sink = true;
        }
    }
    if (sink){
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}