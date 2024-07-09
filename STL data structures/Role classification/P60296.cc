#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

int main() {
    map<string, pair<int, bool>> data_base;        //map<nombre jugador, elo y estado>
    map<string, pair<int, bool>>::iterator it1;
    map<string, pair<int, bool>>::iterator it2;
    string player1;
    string player2;
    string instruction;
    
    while (cin >> instruction) {
        if (instruction == "LOGIN") {
            cin >> player1;
            it1 = data_base.find(player1);
            if (it1 == data_base.end()) data_base.insert({player1,{1200,true}});
            else it1->second.second = true;
        }

        else if (instruction == "LOGOUT") {
            cin >> player1;
            it1 = data_base.find(player1);
            if (it1 != data_base.end()) it1->second.second = false;
        }

        else if (instruction == "PLAY") {
            cin >> player1 >> player2;
            it1 = data_base.find(player1);
            it2 = data_base.find(player2);

            if (it1 == data_base.end() or it2 == data_base.end() or it1->second.second == false or it2->second.second == false)
                cout << "jugador(s) no connectat(s)" << endl;
            else {
                it1->second.first += 10;
                if (it2->second.first >= 1210) it2->second.first -= 10;
            }
        }

        else if (instruction == "GET_ELO") {
            cin >> player1;
            it1 = data_base.find(player1);
            cout << it1->first << " " << it1->second.first << endl;
        }
    }

    cout << endl;
    cout << "RANKING" << endl;
    
    map<int, set<string>> rank;         //map<elo, nombre jugador>
    map<int, set<string>>::iterator it3;
    it1 = data_base.begin();
    while (it1 != data_base.end()) {
        it3 = rank.find(it1->second.first);
        if (it3 == rank.end()) rank.insert({it1->second.first, {it1->first}});
        else it3->second.insert(it1->first);
        ++it1;
    }

    set<string>::iterator it4;
    it3 = rank.end();

    while (it3 != rank.begin()) {
        --it3;
        it4 = it3->second.begin();
        while (it4 != it3->second.end()) {
            cout << (*it4) << " " << it3->first << endl;
            ++it4;
        }
    }
}