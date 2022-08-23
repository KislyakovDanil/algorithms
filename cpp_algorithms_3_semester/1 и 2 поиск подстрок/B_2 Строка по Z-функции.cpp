#include <iostream>
#include <vector>
using namespace std;

const int alphabet_size = 26;

class Converter{
public:
    static vector<int> string_to_prefix_function(const string& str);
    static vector<int> string_to_z_function(const string& str);
    static string prefix_function_to_string(const vector<int>& prefix_function);
    static string z_function_to_string(const vector<int>& z_function);
    static vector<int> prefix_function_to_z_function(const vector<int>& prefix_function);
    static vector<int> z_function_to_prefix_function(const vector<int>& z_function);
};

vector<int> Converter::string_to_prefix_function(const string& str){ //вычисление префикс-функции строки
    vector<int> prefix_function(1, 0);
    for (int i = 1; i < str.size(); ++i){
        int current_char_prefix = prefix_function[i - 1];
        while (current_char_prefix > 0 && str[i] != str[current_char_prefix]){
            current_char_prefix = prefix_function[current_char_prefix - 1];
        }
        if (str[i] == str[current_char_prefix]){
            ++current_char_prefix;
        }
        prefix_function.push_back(current_char_prefix);
    }
    return  prefix_function;
}

vector<int> Converter::string_to_z_function(const string& str){ //вычисление z-функции строки
    vector<int> z_function(1, str.size());
    int left = 0, right = 0;
    for (int i = 1; i < str.size(); ++i){
        int temp = max(0, min(right - i, z_function[i - left]));
        while (i + temp < str.size() && str[temp] == str[i + temp]){
            temp++;
        }
        if (i + temp > right){
            left = i;
            right = i + temp;
        }
        z_function.push_back(temp);
    }
    return z_function;
}

string Converter::prefix_function_to_string(const vector<int>& prefix_function){ //вычисление лексикографически-минимальной строки по префикс-функции
    string str = "a";
    for (int i = 1; i < prefix_function.size(); ++i){
        if (prefix_function[i] == 0){
            int pos = prefix_function[i - 1];
            vector<bool> accept_symb(alphabet_size, true); // разрешённые символы
            accept_symb[0] = false;
            while (pos > 0){// запрещаем символы, которые могут сделать prefix_function[i] != 0
                accept_symb[str[pos] - 'a'] = false;
                pos = prefix_function[pos-1];
            }
            for (int j = 0; j < alphabet_size; ++j){
                if (accept_symb[j]){
                    str += (char)('a' + j);//минимум из символов, которых нет в stop_symb
                    break;
                }
            }
        } else {
            str += str[prefix_function[i] - 1];
        }
    }
    return str;
}

string Converter::z_function_to_string(const vector<int>& z_function){ //вычисление лексикографически-минимальной строки по z-функции
    string str = "a";
    vector<bool> accept_symb(alphabet_size, true); // разрешённые символы
    accept_symb[0] = false;
    int known_pref_len = 0; // число предстоящих символов, которые знаем
    int char_pos = 0; // номер позиции эквивалентной текущей
    for (int i = 1; i < z_function.size(); ++i) {
        if (z_function[i] > known_pref_len) {//можем понять вид более днинной строки
            known_pref_len = z_function[i];
            accept_symb.clear();
            accept_symb.resize(alphabet_size, true);
            char_pos = 0;
        }
        if (known_pref_len > 0){
            str += str[char_pos];
            if (z_function[i] == known_pref_len && i > known_pref_len){// запрещаем значение, которое может сделать z_function[i] больше, чем он есть на самом деле
                accept_symb[str[known_pref_len] - 'a'] = false;
            }
            ++char_pos;
            --known_pref_len;
        } else { // z_function[i] == 0, known_pref_len == 0
            for (int j = 1; j < alphabet_size; ++j){
                if (accept_symb[j]){
                    str += (char)('a' + j);//минимум из символов, которых нет в accept_symb
                    break;
                }
            }
            accept_symb.clear();
            accept_symb.resize(alphabet_size, true);
        }

    }
    return str;
}

vector<int> Converter::prefix_function_to_z_function(const vector<int>& prefix_function){
    return string_to_z_function(prefix_function_to_string(prefix_function));
}

vector<int> Converter::z_function_to_prefix_function(const vector<int>& z_function){
    return string_to_prefix_function(z_function_to_string(z_function));
}

int main(){
    vector<int> z_function(0, 0);//строка и шаблон
    string input_str;
    getline(cin, input_str);// считываем строку неизвестного размера
    int count = 0;
    for (char i: input_str){
        if (i == ' '){
            count = 0;
        } else {
            if (count == 0){
                z_function.push_back(i - '0');
            } else {
                z_function.back() = z_function.back() * 10 + i - '0';
            }
            ++count;
        }
    }
    cout << Converter::z_function_to_string(z_function);
    return 0;
}