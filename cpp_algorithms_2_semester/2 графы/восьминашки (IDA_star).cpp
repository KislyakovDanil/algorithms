#include <iostream>
#include <vector>
#include <queue>
using namespace std;


struct way{
    way(int c, string r, int l):config(c), route(r), length_way(l){};
    int config;
    string route;
    int length_way;//длина потенциального остатка пути
};

struct comp{
    bool operator()(way& a, way& b) {
        return a.length_way + a.route.size() > b.length_way + b.route.size();
    }
};

int v_to_int(vector<int>& v){
    int config = 0;
    for(int i = 1; i < 10; ++i){
        if (v[i] == 9){
            config = config * 9;
        } else {
            config = config * 9 + v[i];
        }
    }
    return config;
}

vector<int> int_to_v(int ulli){
    vector<int> config(10, 0);
    for(int i = 1; i < 10; ++i){
        if (ulli % 9 == 0){
            config[10-i] = 9;
        } else {
            config[10-i] = ulli % 9;
        }
        ulli = ulli / 9;
    }
    return config;
}

int conflicts(vector<int>& config){
    int sum = 0;
    for (int i = 1; i < 10; ++i) {
        for (int j = i + 1; j < 10; ++j) {
            if (config[i] != 9 && config[j] != 9  && i < j && config[j] < config[i]) {
                if (config[i] % 3 == config[j] % 3 && config[i] % 3 == i % 3 && config[j] % 3 == j % 3) {
                    sum += 2;
                }
                if ((config[i] - 1) / 3 == (config[j] - 1) / 3 && ((config[i] - 1) / 3 == (i - 1) / 3) && ((config[j] - 1) / 3 == (j - 1) / 3)) {
                    sum += 2;
                }
            }
        }
    }
    return sum;
}

int length_remaining_way(int& config_ulli){//оценка остатка пути
    vector<int> config = int_to_v(config_ulli);
    int sum = 0;
    bool last_step = true;
    for(int i = 1; i < 10; ++i){
        if (config[i] != 9){
            sum += (abs((config[i]-1) % 3 - (i-1) % 3) + abs((config[i]-1) / 3 - (i-1) / 3));
        }
        if ((config[i] == 8 && i % 3 == 0) || (config[i] == 6 && (i-1) / 3 == 2)){
            last_step = false;
        }
    }
    if (last_step){
        sum +=2;
    }
    if (config[2] == 2){
        if (config[4] == 4 && config[1] != 1){
            sum += 4;
        }
        if (config[6] == 6 && config[3] != 3){
            sum += 4;
        }
    }
    if (config[8] == 8){
        if (config[4] == 4 && config[7] != 7){
            sum += 4;
        }
        if (config[6] == 6 && config[9] != 9){
            sum += 4;
        }
    }
    sum +=  conflicts(config);
    return sum;
}

vector<way> give_successors(way& promising){
    vector<int> config = int_to_v(promising.config);
    vector<way> successors;
    int zero_pos = 0;
    for(int i = 1; i < 10; ++i){
        if (config[i] == 9){
            zero_pos = i;
        }
    }
    if (zero_pos - 3 > 0){
        vector<int> temp = config;
        swap(temp[zero_pos], temp[zero_pos - 3]);
        int succ_conf = v_to_int(temp);
        way successor(succ_conf, promising.route + "U", length_remaining_way(succ_conf));
        successors.push_back(successor);
    }
    if (zero_pos + 3 < 10){
        vector<int> temp = config;
        swap(temp[zero_pos], temp[zero_pos + 3]);
        int succ_conf = v_to_int(temp);
        way successor(succ_conf, promising.route + "D", length_remaining_way(succ_conf));
        successors.push_back(successor);
    }
    if (zero_pos % 3 != 0){
        vector<int> temp = config;
        swap(temp[zero_pos], temp[zero_pos + 1]);
        int succ_conf = v_to_int(temp);
        way successor(succ_conf, promising.route + "R", length_remaining_way(succ_conf));
        successors.push_back(successor);
    }
    if (zero_pos % 3 != 1){
        vector<int> temp = config;
        swap(temp[zero_pos], temp[zero_pos - 1]);
        int succ_conf = v_to_int(temp);
        way successor(succ_conf, promising.route + "L", length_remaining_way(succ_conf));
        successors.push_back(successor);
    }
    return successors;
}

bool way_in_vector(int& config, vector<way>& ways){
    for (way elem: ways){
        if (config == elem.config){
            return true;
        }
    }
    return false;
}


way search(vector<way>& ways, int lim){
    way node = ways.back();
    if (node.config == 54480996 || node.length_way + node.route.size() > lim){
        return node;
    }
    priority_queue<way, vector<way>, comp> successors;
    for (way succ: give_successors(node)){
        successors.push(succ);
    }
    int min = 100;
    while (!successors.empty()){
        way succ = successors.top();
        successors.pop();
        if (!way_in_vector(succ.config, ways)) {
            ways.push_back(succ);
            way t = search(ways, lim);
            if (t.config == 54480996) {
                return t;
            }
            if (t.route.size() + t.length_way < min) {
                min = t.route.size() + t.length_way;
            }
            ways.pop_back();
        }
    }
    node.length_way = min - node.route.size();
    return node;
}

string IDA_star(int config){
    int lim = length_remaining_way(config);
    way start(config, "", lim);
    vector<way> ways;
    ways.push_back(start);
    while (true){
        way result = search(ways, lim);
        if (result.config == 54480996) {
            return result.route;
        }
        lim = result.route.size() + result.length_way;
    }
}

int main() {
    vector<int> config(10);
    for (int i = 1; i < 10; ++i){
        int num;
        cin >> num;
        if (num == 0){
            num = 9;
        }
        config[i] = num;
    }
    int sum_checker = 0;//проверка на решаемость
    for (int i = 1; i < 10; ++i){
        if (config[i] !=9) {
            for (int j = i+1; j < 10; ++j) {
                if (config[i] > config[j]) {
                    ++sum_checker;
                }
            }
        }
    }
    if (sum_checker % 2 == 0){
        string route = IDA_star(v_to_int(config));
        cout << route.size() << endl << route;
    } else {
        cout << -1;
    }
}