#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string,int> m;
    string s;
    while (cin >> s) {
        map<string,int>::iterator it = m.find(s);
        string a;
        cin >> a;
        if (it != m.end()) {
            if (a == "enters")  cout << s << " is already in the casino" << endl;
            else if (a == "wins") {
                int k;
                cin >> k;
                it->second = it->second + k;
            }
            else if (a == "leaves") {
                cout << s << " has won " << it->second << endl;
                m.erase(it);
            }
        }
        else {
            if (a == "enters") m.insert({s,0});
            else if (a == "wins")  {
                int k;
                cin >> k;
                cout << s << " is not in the casino" << endl;
            }
            else if (a == "leaves") cout << s << " is not in the casino" << endl;
        }
    }

    cout << "----------" << endl;
    for ( map<string,int>::iterator it = m.begin(); it != m.end(); ++it) {
        cout << it->first << " is winning " << it->second << endl;
    }
}