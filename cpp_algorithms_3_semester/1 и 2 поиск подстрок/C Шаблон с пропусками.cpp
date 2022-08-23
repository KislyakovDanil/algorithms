#include <iostream>
#include <vector>
using namespace std;

int alphabet_size = 26;

struct Vertex { // вершина бора
    Vertex(int p, char pc):parent_char(pc), parent(p), suf_link(-1), edges(alphabet_size, -1), travels(alphabet_size, -1){};
    vector<int> edges; // сыновья
    vector<int> travels; // переходы
    int suf_link; // суффиксная ссылка
    int parent; // родитель
    char parent_char; // символ, ведущий к родителю
    vector<int> leaf_pattern_num; // номера подшаблонов, за которые отвечает терминал
};

class AhoCorasick { // реализация алгоритма Ахо-Корасика
public: // везде ниже p - шаблон, s - строка, в которой ищем вхождения шаблона,  i - № вершины, c - символ, по которому осуществляется переход
    AhoCorasick(const string& pattern);
    vector<int> occurrence_search(const string& str); // поиск вхождений шаблона в строку
private:
    void find_sub_patterns(const string& pattern); // поиск подшаблонов, разделённых ?
    int get_suf_link(int i); // получение суфиксной ссылки
    int get_link(int i, char c); // получение сжатой суфиксной ссылки
    int pattern_size; // шаблон
    vector<Vertex> prefix_tree; // вершины бора
    vector<pair<int, int>> sub_patterns; // пары начало-конец подшаблонов
};

AhoCorasick::AhoCorasick(const string& pattern): prefix_tree(1, Vertex(0, -1)), pattern_size(pattern.size()) {
    prefix_tree[0].suf_link = 0;
    find_sub_patterns(pattern);
    for (int i = 0; i < sub_patterns.size(); ++i) { // строим бор
        int vert_num = 0;
        for (int j = sub_patterns[i].first; j <= sub_patterns[i].second; ++j) {
            char c = pattern[j] - 'a';
            if (prefix_tree[vert_num].edges[c] == -1) { // если ещё нет такого ребра
                prefix_tree.push_back(Vertex(vert_num, c));
                prefix_tree[vert_num].edges[c] = prefix_tree.size() - 1;
            }
            vert_num = prefix_tree[vert_num].edges[c];
        }
        prefix_tree[vert_num].leaf_pattern_num.push_back(i);
    }
}

int AhoCorasick::get_suf_link(int i) {
    if (prefix_tree[i].suf_link == -1) { // если ссылка ещё не вычислена
        if (prefix_tree[i].parent == 0) {
            prefix_tree[i].suf_link = 0;
        } else {
            prefix_tree[i].suf_link = get_link(get_suf_link(prefix_tree[i].parent), prefix_tree[i].parent_char);
        }
    }
    return prefix_tree[i].suf_link;
}

int AhoCorasick::get_link(int i, char c) {
    if (prefix_tree[i].travels[c] == -1) { // если переход по символу ещё не вычислен
        if (prefix_tree[i].edges[c] != -1) {
            prefix_tree[i].travels[c] = prefix_tree[i].edges[c];
        } else if (i == 0) {
            prefix_tree[i].travels[c] = 0;
        } else {
            prefix_tree[i].travels[c] = get_link(get_suf_link(i), c);
        }
    }
    return prefix_tree[i].travels[c];
}

void AhoCorasick::find_sub_patterns(const string& pattern) {
    pair<int, int> sub_pattern;
    for (int i = 0; i < pattern.size(); ++i) {
        if (pattern[i] != '?') {
            if (i == 0 || pattern[i - 1] == '?') {
                sub_pattern.first = i;
            }
            if (i == pattern.size() - 1 || pattern[i + 1] == '?') {
                sub_pattern.second = i;
                sub_patterns.push_back(sub_pattern);
            }
        }
    }
}

vector<int> AhoCorasick::occurrence_search(const string& str) {
    vector<int> sub_patterns_occurrences_counter(str.size()); // i элемент = количеству подшаблонов <=> вхождение шаблона на i позиции
    int current_vert = 0;
    for (int i = 0; i < str.size(); ++i) {
        current_vert = get_link(current_vert, str[i] - 'a');
        int u = current_vert;
        while (u != 0){ // поиск терминальных вершин по суфиксам уже прочитанной строки
            if (!prefix_tree[u].leaf_pattern_num.empty()) {
                for (int j = 0; j < prefix_tree[u].leaf_pattern_num.size(); ++j) {
                    if ((i - sub_patterns[prefix_tree[u].leaf_pattern_num[j]].second >= 0) && (i - sub_patterns[prefix_tree[u].leaf_pattern_num[j]].second <= str.size() - pattern_size)) {
                        ++sub_patterns_occurrences_counter[i - sub_patterns[prefix_tree[u].leaf_pattern_num[j]].second];
                    }
                }
            }
            u = get_suf_link(u);
        }
    }
    vector<int> answer;
    for (int i = 0; i <= str.size() - pattern_size; ++i) {
        if (sub_patterns_occurrences_counter[i] == sub_patterns.size()) {
            answer.push_back(i);
        }
    }
    return answer;
}

int main() {
    string pattern, str;
    cin >> pattern >> str;
    if (pattern.size() > str.size()){
        return 0;
    }
    AhoCorasick aho_corasick(pattern);
    vector<int> occurrences = aho_corasick.occurrence_search(str);
    for (int i = 0; i < occurrences.size(); ++i) {
        cout << occurrences[i] << " ";
    }
    return 0;
}