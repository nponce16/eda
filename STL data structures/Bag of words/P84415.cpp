#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string,int> bag;
    string op, word;
    while (cin >> op) {
        if (op == "store") {
            cin >> word;
            auto it = bag.find(word);
            if (it != bag.end()) {
                it->second += 1;
            }
            else bag.insert({word,1});
            continue;
        }
        if (op == "delete") {
            cin >> word;
            auto it = bag.find(word);
            if (it != bag.end()) {
                it->second -= 1;
                if (it->second == 0) bag.erase(word);
            }
            continue;
        }
        if (op == "maximum?") {
            if (not bag.empty()) {
                auto it = bag.end();
                --it;
                cout << "maximum: " << it->first << ", " << it->second << " time(s)" << endl;
            }
            else cout << "indefinite maximum" << endl;
            continue;
        }
        if (op == "minimum?") {
            if (not bag.empty()) {
                auto it = bag.begin();
                cout << "minimum: " << it->first << ", " << it->second << " time(s)" << endl;
            }
            else cout << "indefinite minimum" << endl;
        }
    }
}