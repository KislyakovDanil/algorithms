#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;


struct way{
    way(unsigned long long c, string r, int l):config(c), route(r), length_way(l){};
    unsigned long long config;
    string route;
    int length_way;//длина потенциального остатка пути
};

struct comp{
    bool operator()(way& a, way& b) {
        return a.length_way*1.15 + a.route.size() > b.length_way*1.15 + b.route.size();
    }
};

unsigned long long v_to_ulli(vector<int>& v){
    unsigned long long config = 0;
    for(int i = 1; i < 17; ++i){
        if (v[i] == 16){
            config = config * 16;
        } else {
            config = config * 16 + v[i];
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

int conflicts(vector<int>& config){
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

int length_remaining_way(unsigned long long& config_ulli){//оценка остатка пути
    vector<int> config = ulli_to_v(config_ulli);
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

vector<way> give_successors(way& promising, unordered_set<size_t>& visited){
    vector<way> successors;
    vector<int> config = ulli_to_v(promising.config);
    int zero_pos = 0;
    for(int i = 1; i < 17; ++i){
        if (config[i] == 16){
            zero_pos = i;
        }
    }
    if (zero_pos - 4 > 0){
        vector<int> temp = config;
        swap(temp[zero_pos], temp[zero_pos - 4]);
        unsigned long long succ_conf = v_to_ulli(temp);
        way successor(succ_conf, promising.route + "D", length_remaining_way(succ_conf));
        string s = to_string(successor.config) + to_string(successor.route.size());
        if (visited.count(hash<string>()(s)) == 0){
            visited.insert(hash<string>()(s));
            successors.push_back(successor);
        }
    }
    if (zero_pos + 4 < 17){
        vector<int> temp = config;
        swap(temp[zero_pos], temp[zero_pos + 4]);
        unsigned long long succ_conf = v_to_ulli(temp);
        way successor(succ_conf, promising.route + "U", length_remaining_way(succ_conf));
        string s = to_string(successor.config) + to_string(successor.route.size());
        if (visited.count(hash<string>()(s)) == 0){
            visited.insert(hash<string>()(s));
            successors.push_back(successor);
        }
    }
    if (zero_pos % 4 != 0){
        vector<int> temp = config;
        swap(temp[zero_pos], temp[zero_pos + 1]);
        unsigned long long succ_conf = v_to_ulli(temp);
        way successor(succ_conf, promising.route + "L", length_remaining_way(succ_conf));
        string s = to_string(successor.config) + to_string(successor.route.size());
        if (visited.count(hash<string>()(s)) == 0){
            visited.insert(hash<string>()(s));
            successors.push_back(successor);
        }
    }
    if (zero_pos % 4 != 1){
        vector<int> temp = config;
        swap(temp[zero_pos], temp[zero_pos - 1]);
        unsigned long long succ_conf = v_to_ulli(temp);
        way successor(succ_conf, promising.route + "R", length_remaining_way(succ_conf));
        string s = to_string(successor.config) + to_string(successor.route.size());
        if (visited.count(hash<string>()(s)) == 0){
            visited.insert(hash<string>()(s));
            successors.push_back(successor);
        }
    }
    return successors;
}

string A_star(unsigned long long config){
    unordered_set<size_t> visited;
    way start(config, "", length_remaining_way(config));
    priority_queue<way, vector<way>, comp> configs;
    configs.push(start);
    while (!configs.empty()){
        way promising = configs.top();
        configs.pop();
        if(promising.config == 1311768467463790320){
            return promising.route;
        }
        for (way successor: give_successors(promising, visited)){
            configs.push(successor);
        }
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
        string route = A_star(v_to_ulli(config));
        cout << route.size() << endl << route;
    } else {
        cout << -1;
    }
}