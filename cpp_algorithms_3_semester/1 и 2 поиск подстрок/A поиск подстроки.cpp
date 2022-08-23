#include <iostream>
#include <vector>
using namespace std;

vector<int> prefix_function(const string& str){ //вычисление префикс-функции строки
    vector<int> p_f(1, 0);
    for(int i = 1; i < str.size(); ++i){
		int current_char_prefix = p_f[i - 1];
		while (current_char_prefix > 0 && str[i] != str[current_char_prefix]){
            current_char_prefix = p_f[current_char_prefix - 1];
        }
        if (str[i] == str[current_char_prefix]){
			++current_char_prefix;
        }
        p_f.push_back(current_char_prefix);
    }
	return  p_f;
}

vector<int> knut_morris_pratt(const string& pattern, const string& input_str){ //алгоритм Кнута-Морриса-Пратта
    vector<int> p_f = prefix_function(pattern);
    vector<int> positions(0, 0);
   int previous_char_p_f = 0;
    for(int i = 0; i < input_str.size(); ++i){
        int current_char_p_f = previous_char_p_f;
        while (current_char_p_f > 0 && input_str[i] != pattern[current_char_p_f]){
            current_char_p_f = p_f[current_char_p_f - 1];
        }
        if (input_str[i] == pattern[current_char_p_f]){
            ++current_char_p_f;
        }
        if (current_char_p_f == pattern.size()){
            positions.push_back(i - p_f.size() + 1);
        }
        previous_char_p_f = current_char_p_f;
    }
    return positions;
}

int main(){
    string pattern = "", input_str = "";
    cin >> pattern >> input_str;
    vector<int> positions = knut_morris_pratt(pattern, input_str);
    for (int i: positions){
        cout << i << " ";
    }
    return 0;
}