#include <iostream>
#include <vector>
using namespace std;

string routs = "DULR";
vector<int> displasement = {-4, 4, 1, -1};

struct way{
    way(unsigned long long c, string r, int l, int t):config(c), route(r), length_way(l), traveled(t){};
    unsigned long long config;//поле
    string route;//путь
    int length_way;//длина потенциального остатка пути
    int traveled;//пройденный путь
};

unsigned long long v_to_ulli(const vector<int>& v){
    unsigned long long config = 0;
    for(int i: v){
        if (i == 16){
            config = config * 16;
        } else {
            config = config * 16 + i;
        }
    }
    return config;
}

vector<int> ulli_to_v(unsigned long long ulli){
    vector<int> config(17, 0);
    for(int i = 1; i < 17; ++i){
        if (ulli % 16 == 0){
            config[17-i] = 16;
        } else {
            config[17-i] = ulli % 16;
        }
        ulli = ulli / 16;
    }
    return config;
}

int conflicts(const vector<int>& config){
    int sum = 0;
    for (int i = 1; i < 17; ++i) {
        for (int j = i + 1; j < 17; ++j) {
            if (config[i] != 16 && config[j] != 16  && i < j && config[j] < config[i]) {
                if (config[i] % 4 == config[j] % 4 && config[i] % 4 == i % 4 && config[j] % 4 == j % 4) {
                    sum += 2;
                }
                if ((config[i] - 1) / 4 == (config[j] - 1) / 4 && ((config[i] - 1) / 4 == (i - 1) / 4) && ((config[j] - 1) / 4 == (j - 1) / 4)) {
                    sum += 2;
                }
            }
        }
    }
    return sum;
}

int length_remaining_way(const vector<int>& config){//оценка остатка пути
    int sum = 0;
    bool last_step = true;
    for(int i = 1; i < 17; ++i){
        if (config[i] != 16){
            sum += (abs((config[i]-1) % 4 - (i-1) % 4) + abs((config[i]-1) / 4 - (i-1) / 4));
        }
        if ((config[i] == 15 && i % 4 == 0) || (config[i] == 12 && (i-1) / 4 == 3)){
            last_step = false;
        }
    }
    if (last_step){
        sum +=2;
    }
    if (config[2] == 2 && config[5] == 5 && config[1] != 1){
        sum += 4;
    }
    if (config[3] == 3 && config[8] == 8 && config[4] != 4){
        sum += 4;
    }
    if (config[9] == 9 && config[14] == 14 && config[13] != 13){
        sum += 4;
    }
    if (config[12] == 12 && config[15] == 15 && config[16] != 16){
        sum += 4;
    }
    sum +=  conflicts(config);
    return sum;
}

vector<way> give_successors(const way& promising){//потомки
    vector<int> config = ulli_to_v(promising.config);
    vector<way> successors;
    pair<int,int> zero_pos(0,0);
    int z_p = 0;
    for(int i = 1; i < 17; ++i){
        if (config[i] == 16){
            zero_pos.first = (i - 1) % 4;
            zero_pos.second = (i - 1) / 4;
            z_p = i;
        }
    }
    vector<int> comps_elem = {zero_pos.second, zero_pos.second - 3, zero_pos.first - 3, zero_pos.first};
    for (int i = 0; i < 4; ++i){
        if (comps_elem[i] != 0){
            vector<int> temp = config;
            swap(temp[z_p], temp[z_p + displasement[i]]);
            way successor(v_to_ulli(temp), promising.route + routs[i], length_remaining_way(temp), promising.traveled + 1);
            successors.push_back(successor);
        }
    }
    return successors;
}

bool way_in_vector(const unsigned long long config, const vector<way>& ways){
    for (way elem: ways){
        if (config == elem.config){
            return true;
        }
    }
    return false;
}

way search(vector<way>& ways, int lim){
    way node = ways.back();
    if (node.config == 1311768467463790320 || node.length_way + node.traveled > lim){
        return node;
    }
    int min = 100;
    for (way succ: give_successors(node)){
        if (!way_in_vector(succ.config, ways)) {
            ways.push_back(succ);
            way t = search(ways, lim);
            if (t.config == 1311768467463790320) {
                return t;
            }
            if (t.traveled + t.length_way < min) {
                min = t.traveled + t.length_way;
            }
            ways.pop_back();
        }
    }
    node.length_way = min - node.traveled;
    return node;
}

string IDA_star(vector<int>& config){
    int lim = length_remaining_way(config);
    way start(v_to_ulli(config), "", lim, 0);
    vector<way> ways;
    ways.push_back(start);
    while (true){
        way result = search(ways, lim);
        if (result.config == 1311768467463790320) {
            return result.route;
        }
        lim = result.traveled + result.length_way;
    }
}

int main() {
    vector<int> config(17, 0);
    for (int i = 1; i < 17; ++i){
        int num;
        cin >> num;
        if (num == 0){
            num = 16;
        }
        config[i] = num;
    }
    int sum_checker = 0;//проверка на решаемость
    for (int i = 1; i < 17; ++i){
        if (config[i] !=16) {
            for (int j = i+1; j < 17; ++j) {
                if (config[i] > config[j]) {
                    ++sum_checker;
                }
            }
        } else {
            sum_checker += (i-1)/4 + 1;
        }
    }
    if (sum_checker % 2 == 0){
        string route = IDA_star(config);
        cout << route.size() << endl << route;
    } else {
        cout << -1;
    }
}