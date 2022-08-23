#include <iostream>
#include <vector>
using namespace std;

class Converter{
public:
    vector<int> prefix_function(const string& s);
    vector<int> z_function(const string& s);
    string prefix_function_to_string(const vector<int>& p_f);
    string z_function_to_string(const vector<int>& z_f);
    vector<int> prefix_function_to_z_function(const vector<int>& p_f);
    vector<int> z_function_to_prefix_function(const vector<int>& z_f);
};

vector<int> Converter::prefix_function(const string& s){ //вычисление префикс-функции строки
    vector<int> p_f(1,0);
    for(int i = 1; i < s.size(); ++i){
        int current_char_prefix = p_f[i - 1];
        while (current_char_prefix > 0 && s[i] != s[current_char_prefix]){
            current_char_prefix = p_f[current_char_prefix - 1];
        }
        if (s[i] == s[current_char_prefix]){
            ++current_char_prefix;
        }
        p_f.push_back(current_char_prefix);
    }
    return  p_f;
}

vector<int> Converter::z_function(const string& s){ //вычисление z-функции строки
    vector<int> z_f(1, s.size());
    int left = 0, right = 0;
    for(int i = 1; i < s.size(); ++i){
        int temp = max(0, min(right - i, z_f[i - left]));
        while (i + temp < s.size() && s[temp] == s[i + temp]){
            temp++;
        }
        if (i + temp > right){
            left = i;
            right = i + temp;
        }
        z_f.push_back(temp);
    }
    return  z_f;
}

string Converter::prefix_function_to_string(const vector<int>& p_f){ //вычисление лексикографически-минимальной строки по префикс-функции
    string s = "a";
    for(int i = 1; i < p_f.size(); ++i){
        if (p_f[i] == 0){
            int pos = p_f[i - 1];
            vector<bool> accept_symb(28, true); // разрешённые символы
            accept_symb[0] = false;
            while (pos > 0){// запрещаем символы, которые могут сделать p_f[i] != 0
                accept_symb[s[pos] - 'a'] = false;
                pos = p_f[pos-1];
            }
            for (int j = 0; j < 28; ++j){
                if (accept_symb[j]){
                    s += (char)('a' + j);//минимум из символов, которых нет в stop_symb
                    break;
                }
            }
        } else {
            s += s[p_f[i] - 1];
        }
    }
    return s;
}

string Converter::z_function_to_string(const vector<int>& z_f){ //вычисление лексикографически-минимальной строки по z-функции
    string s = "a";
    vector<bool> accept_symb(28, true); // разрешённые символы
    accept_symb[0] = false;
    int known_pref_len = 0; // число предстоящих символов, которые знаем
    int char_pos = 0; // номер позиции эквивалентной текущей
    for (int i = 1; i < z_f.size(); ++i) {
        if (z_f[i] > known_pref_len) {//можем понять вид более днинной строки
            known_pref_len = z_f[i];
            accept_symb.clear();
            accept_symb.resize(28, true);
            char_pos = 0;
        }
        if (known_pref_len > 0){
            s += s[char_pos];
            if (z_f[i] == known_pref_len && i > known_pref_len){// запрещаем значение, которое может сделать z_f[i] больше, чем он есть на самом деле
                accept_symb[s[known_pref_len] - 'a'] = false;
            }
            ++char_pos;
            --known_pref_len;
        } else { // z_f[i] == 0, known_pref_len == 0
            for (int j = 1; j < 28; ++j){
                if (accept_symb[j]){
                    s += (char)('a' + j);//минимум из символов, которых нет в accept_symb
                    break;
                }
            }
            accept_symb.clear();
            accept_symb.resize(28, true);
        }

    }
    return s;
}

vector<int> Converter::prefix_function_to_z_function(const vector<int>& p_f){
    return z_function(prefix_function_to_string(p_f));
}

vector<int> Converter::z_function_to_prefix_function(const vector<int>& z_f){
    return prefix_function(z_function_to_string(z_f));
}

int main(){
    vector<int> p_f(0,0);//строка и шаблон
    Converter converter;
    string s;
    getline(cin, s);// считываем строку неизвестного размера
    int count = 0;
    for(char i: s){
        if (i == ' '){
            count = 0;
        } else {
            if (count == 0){
                p_f.push_back(i - '0');
            } else {
                p_f.back() = p_f.back() * 10 + i - '0';
            }
            ++count;
        }
    }
    cout << converter.prefix_function_to_string(p_f);
    return 0;
}