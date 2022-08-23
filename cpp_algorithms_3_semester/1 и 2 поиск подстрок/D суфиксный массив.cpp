#include <iostream>
#include <vector>
using namespace std;

const int alphabet_size = 27;

vector<int> build_lcp(const vector<int>& transpos, const vector<vector<int>>& eq_classes) {
    vector<int> lcp(transpos.size() - 2, 0);
    for (int i = 1; i < transpos.size() - 1; ++i) {
        int first = transpos[i];
        int second = transpos[i + 1];
        for (int k = static_cast<int>(eq_classes.size()) - 1; k >= 0; --k) {
            if (eq_classes[k][first] != eq_classes[k][second]) {
                continue;
            }
            int k_degree_of_2 = 1 << k; // 2^k
            lcp[i - 1] += k_degree_of_2;
            first += k_degree_of_2;
            second += k_degree_of_2;
        }
    }
    return lcp;
}

void step (vector<int>& transpos, vector<vector<int>>& eq_classes) {
    int step_num = static_cast<int>(eq_classes.size()) - 1;
    int step_num_degree_of_2 = 1 << step_num; // 2^step_num
    vector<int> temp_transpos(transpos.size());
    for (int i = 0; i < transpos.size(); ++i) {
        temp_transpos[i] = max(transpos[i] - step_num_degree_of_2, (transpos[i] - step_num_degree_of_2 + static_cast<int>(transpos.size())) % static_cast<int>(transpos.size()));
    }
    vector<int> count(eq_classes[step_num].size(), 0);
    for (int i = 0; i < transpos.size(); ++i) {
        ++count[eq_classes[step_num][temp_transpos[i]]];
    }
    for (int i = 1; i < eq_classes[step_num].size(); ++i) {
        count[i] += count[i - 1];
    }
    for (int i = static_cast<int>(transpos.size()) - 1; i >= 0; --i) {
        transpos[--count[eq_classes[step_num][temp_transpos[i]]]] = temp_transpos[i];
    }
    eq_classes.push_back(vector<int>(transpos.size(), 0)); // cчитаем новые классы эквивалентности
    int classes_num = 1;
    for (int i = 1; i < transpos.size(); ++i) {
        int shift_1 = (transpos[i] + step_num_degree_of_2) % static_cast<int>(transpos.size()); // сортировки по уже обработанной длине подстрок
        int shift_2 = (transpos[i - 1] + step_num_degree_of_2) % static_cast<int>(transpos.size());
        if (eq_classes[step_num][transpos[i]] != eq_classes[step_num][transpos[i - 1]] || eq_classes[step_num][shift_1] != eq_classes[step_num][shift_2]) {
            ++classes_num;
        }
        eq_classes[step_num + 1][transpos[i]] = classes_num - 1;
    }
}

int substr_num (string& str) {
    str += '#';
    vector<int> transpos(str.size()); // текущее состояние сортировки, в итоге -- суфф масс
    vector<vector<int>> eq_classes(1, vector<int>(str.size(), 0)); // eq_classes[i] -- классы эквивалентности по прочитанной подстроке на i-м шаге
    vector<int> count(alphabet_size, 0); // сортируем подсчетом по первому символу суфикса
    for (char symbol: str) {
        switch(symbol)
        {
            case '#':
                ++count[0];
                break;
            default:
                ++count[symbol - 'a' + 1];
                break;
        }

    }
    for (int i = 1; i < alphabet_size; ++i) {
        count[i] += count[i - 1]; // концы групп
    }
    for (int i = 0; i < str.size(); ++i) {
        switch(str[i]) {
            case '#':
                transpos[--count[0]] = i;
                break;
            default:
                transpos[--count[str[i] - 'a' + 1]] = i;
                break;
        }
    }
    int classes_num = 1; // число классов
    for (int i = 1; i < str.size(); ++i) {
        if (str[transpos[i]] != str[transpos[i - 1]]) {
            ++classes_num;
        }
        eq_classes[0][transpos[i]] = classes_num - 1;
    }
    while ((1 << (eq_classes.size() - 1)) < str.size()) { // повторяем алгоритм, пока длина подстрок не превышает длины строки
        step(transpos, eq_classes);
    }
    vector<int> lcp = build_lcp(transpos, eq_classes); // ищем lcp
    int n = static_cast<int>(str.size()) - 1; // досчитываем ответ
    int counter = 0;
    for (int i = 0; i < n - 1; ++i) {
        counter += n - transpos[i + 1] - lcp[i];
    }
    counter += n - transpos[n];
    return counter;
}

int main() {
    string str;
    cin >> str;
    cout << substr_num(str);
    return 0;
}