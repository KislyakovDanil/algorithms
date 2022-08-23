#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct man {//атлет
    man(int m = 0, int f = 0) :mass(m), force(f)  {}
    int mass;
    int force;
};

struct cmpMassForce{//сравнение атлетов
    bool operator()(man a, man b){
        if(a.mass == b.mass){
            return (a.force < b.force);
        } else {
            return (a.mass < b.mass);
        }
    };
};

int TowerHight (vector<man> Atl){
    int hight = 0;
    int mass = 0;
    for (auto i = Atl.begin(); i < Atl.end(); ++i){
        if(mass <= i->force){
            mass +=i->mass;
            hight +=1;
        }
    }
    return hight;
}

int main() {
    vector<man> Atl;
    while (!(cin.fail() && cin.eof())){
        int m;
        int f;
        cin >> m >> f;
        Atl.emplace_back(m,f);
    }
    sort(Atl.begin(), Atl.end(), cmpMassForce());
    cout << TowerHight(Atl);
    return 0;
    //заменил названия функций, push_back и ещё пару мелочей
}