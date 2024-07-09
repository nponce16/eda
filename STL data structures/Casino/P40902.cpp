#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string,int> profits;  //mapa<nombre, dinero ganado>
    string op;
    string name;

    while(cin >> name >> op) {
        if (op == "enters") {
            //si la persona ya está en el casino
            if (profits.find(name) != profits.end()) {
                cout << name << " is already in the casino" << endl;
            }
            //si no lo estaba
            else profits.insert({name, 0});
            continue;
        }
        if (op == "leaves") {
            if (profits.find(name) == profits.end()) {
                cout << name << " is not in the casino" << endl;
            }
            else {
                auto it = profits.find(name);
                cout << name << " has won " << it->second << endl;
                profits.erase(name);
            }
            continue;
        }
        if (op == "wins") {
            int money;
            cin >> money;
            if (profits.find(name) == profits.end()) {
                cout << name << " is not in the casino" << endl;
            }
            else {
                auto it = profits.find(name);
                it->second += money;
            }
        }
    }

    cout << "----------" << endl;
    for (auto it = profits.begin(); it != profits.end(); ++it) {
        cout << it->first << " is winning " << it->second << endl;
    }
}