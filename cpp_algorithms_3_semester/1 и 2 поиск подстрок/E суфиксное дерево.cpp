#include <iostream>
#include <vector>
#include <memory>
using namespace std;

const size_t alphabet_size = 28;

int char_to_num(char symbol) {
    if (symbol == '#') {
        return 0;
    } else if (symbol == '$') {
        return 1;
    } else {
        return symbol - 'a' + 2;
    }
}

struct Node {
    int start; //первый символ ребра по которому мы пришли в вершину
    shared_ptr<int> end; //последний символ ребра по которому мы пришли в вершину (указатель чтобы у всех листьев был один конечный элемент)
    shared_ptr<Node> suffix_link;
    int suffix_index; // буква, по которой нужно идти после перехода по суфиксной ссылке
    vector<shared_ptr<Node>> children;
    Node(int s, shared_ptr<int> e, shared_ptr<Node> root): start(s), end(e), suffix_link(root), suffix_index(-1), children(alphabet_size, nullptr) {};
    int get_length();
};

int Node::get_length() {
    return *end - start + 1;
}


class SuffixTree {
public:
    SuffixTree(const string& str);
    shared_ptr<Node> root;
    int tree_size;
private:
    shared_ptr<Node> new_node; // последняя добавленная вершина
    shared_ptr<Node> active_node;
    int active_symbol;
    int active_length;
    int suf_counter; // число необработанных суфиксов
    shared_ptr<int> current_end; // текущий конец
    void step(int i, const string& str);
};

SuffixTree::SuffixTree(const string& str) {
    tree_size = 1;
    active_length = 0;
    suf_counter = 0;
    current_end = make_shared<int>(-1);
    root = make_shared<Node>(Node(-1, current_end, nullptr));
    active_node = root;
    for (int i = 0; i < str.size(); ++i) {
        step(i, str);
    }
}

void SuffixTree::step(int i, const string& str) {
    new_node = nullptr;
    ++suf_counter;
    *current_end += 1;
    while (suf_counter > 0) {
        if (active_length == 0) {
            active_symbol = i;
        }
        if (active_node->children[char_to_num(str[active_symbol])] == nullptr) {
            active_node->children[char_to_num(str[active_symbol])] = make_shared<Node>(Node(i, current_end, root));
            ++tree_size;
            if (new_node != nullptr) {
                new_node->suffix_link = active_node;
                new_node = nullptr;
            }
        } else {
            shared_ptr<Node> inner_node = active_node->children[char_to_num(str[active_symbol])];
            int inner_node_length = inner_node->get_length();
            if (active_length >= inner_node_length) {
                active_symbol += inner_node_length;
                active_length -= inner_node_length;
                active_node = inner_node;
                continue;
            }
            if (str[inner_node->start + active_length] == str[i]) {
                ++active_length;
                if (new_node != nullptr && active_node != root) {
                    new_node->suffix_link = active_node;
                    new_node = nullptr;
                }
                break;
            }
            shared_ptr<Node> split = make_shared<Node>(Node(inner_node->start, make_shared<int>(inner_node->start + active_length - 1), root));
            active_node->children[char_to_num(str[split->start])] = split;
            split->children[char_to_num(str[i])] = make_shared<Node>(Node(i, current_end, root));
            inner_node->start += active_length;
            split->children[char_to_num(str[inner_node->start])] = inner_node;
            tree_size += 2;
            if (new_node != nullptr) {
                new_node->suffix_link = split;
            }
            new_node = split;
        }
        --suf_counter;
        if (active_node == root && active_length > 0) {
            --active_length;
            active_symbol = i - suf_counter + 1;
        } else if (active_node != root) {
            active_node = active_node->suffix_link;
        }
    }
}

void print_subtree(shared_ptr<Node> root, int vert_num, int s_size, int& count) {
    for (shared_ptr<Node> vert: root->children) {
        if (vert == nullptr) {
            continue;
        }
        int str_num = 0;
        int left = vert->start;
        int right = *vert->end + 1;
        if (left >= s_size) {
            str_num = 1;
            left -= s_size;
            right -= s_size;
        } else {
            if (right > s_size) {
                right = s_size;
            }
        }
        cout << "\n" << vert_num << " " << str_num << " " << left << " " << right;
        print_subtree(vert, count, s_size, ++count);
    }
}

int main() {
    string s, t;
    cin >> s;
    cin >> t;
    string s_t = s + t;
    SuffixTree tree(s_t);
    cout << tree.tree_size;
    int count = 0;
    print_subtree(tree.root, 0, static_cast<int>(s.size()), count);
    return 0;
}