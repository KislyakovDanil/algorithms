#include <iostream>
#include <vector>
using namespace std;

int Hash(const string &s, int m, int n) {// хеш-функция строки
    int hash = 0;
    for (int i = 0; i < s.size(); ++ i) {
        hash = (hash * n + s[i]) % m;
    }
    return hash;
}

class HashTable {
public:
    HashTable(string e, string d){
        table.resize(8,e);
        plenum = 0;//заполненность
        empty = e;
        deleted = d;
    }

    //деструктор не нужен т.к. вектор не требует удаления

    bool search(const string& key) {//проверка на наличие
        int h1 = 0;
        int h2 = 0;
        CalcHashs(key, h1, h2, table.size());
        for (string i: table) {
            if (table[h1] == empty) {
                return false;
            }
            if (table[h1] == key) {
                return true;
            }
            h1 = (h1 + h2) % table.size();
        }
        return false;
    }

    bool insert(const string& key) {//вставка
        if(search(key)) {
            return false;
        }
        if (3 * table.size() < 4 * plenum) {
            rehash();
        }
        int h1 = 0;
        int h2 = 0;
        CalcHashs(key, h1, h2, table.size());
        for (string i: table) {
            if (table[h1] == empty || table[h1] == deleted) {
                table[h1] = key;
                plenum++;
                return true;
            }
            h1 = (h1 + h2) % table.size();
        }
        return false;
    }

    bool remove(const string& key) {//удаление
        if(!search(key)) {
            return false;
        }
        int h1 = 0;
        int h2 = 0;
        CalcHashs(key, h1, h2, table.size());
        for (string i: table) {
            if (table[h1] == key) {
                table[h1] = deleted;
                plenum--;
                return true;
            }
            h1 = (h1 + h2) % table.size();
        }
        return false;
    }

private:
    vector<string> table;
    int plenum;//заполненность (количество значащих элементов в таблице)
    string empty;
    string deleted;

    void CalcHashs(const string& key, int& h1, int& h2, int size){
        h1 = Hash(key, size, 11);
        h2 = Hash(key, size, 19);
        if (h2 % 2 == 0){
            h2 += 1;
        }
    }

    void rehash() {//перехеширование
        vector<string> newTable(table.size()*2,empty);
        plenum = 0;
        for (string i: table) {
            if(i != empty && i != deleted) {
                int h1 = 0;
                int h2 = 0;
                CalcHashs(i, h1, h2, newTable.size());
                bool flag = false;
                while (!flag) {
                    if (newTable[h1] == empty) {
                        newTable[h1] = i;
                        plenum++;
                        flag = true;
                    }
                    h1 = (h1 + h2) % newTable.size();
                }
            }
        }
        table = newTable;
    }
};

int main() {
    HashTable table("EMPTY","DELETED");
    char com;
    string key;
    while(cin >> com >> key && !cin.fail()) {
        switch(com) {
            case '?' :
                cout << (table.search(key) ? "OK" : "FAIL") << endl;
                break;
            case '+' :
                cout << (table.insert(key) ? "OK" : "FAIL") << endl;
                break;
            case '-' :
                cout << (table.remove(key) ? "OK" : "FAIL") << endl;
                break;
            default :
                break;
        }
    }
    return 0;
}