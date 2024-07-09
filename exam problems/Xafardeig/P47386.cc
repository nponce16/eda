#include <iostream>
#include <set>
using namespace std;

void escriure_info(const set<pair<string,string>>& parelles, const set<string>& sols) {
    auto it_parelles = parelles.begin();
            auto it_sols = sols.begin();

            cout << "PARELLES:" << endl;
            while (it_parelles != parelles.end()) {
                cout << (*it_parelles).first << ' ' << (*it_parelles).second << endl;
                ++it_parelles;
            }
            cout << "SOLS:" << endl;
            while (it_sols != sols.end()) {
                cout << (*it_sols) << endl;
                ++it_sols;
            }
            cout << "----------" << endl;
}

int main() {
    set<pair<string,string>> parelles;
    set<string> sols;
    string ordre, x, y;

    while (cin >> ordre) {

        if (ordre == "info") {
            escriure_info(parelles, sols);
        }
        else {
            cin >> x >> y;

            auto it = parelles.begin();
            pair<string, string> antParella;

            while (it != parelles.end()) {      //compruebo si hay solteros
                antParella = {(*it).first, (*it).second};
                ++it;
                
                if (antParella.first == x) {
                    sols.insert(antParella.second); 
                    parelles.erase(antParella); 
                }
                else if (antParella.second == x) {
                    sols.insert(antParella.first);
                    parelles.erase(antParella);
                }
                if (antParella.first == y) {
                    sols.insert(antParella.second);
                    parelles.erase(antParella);
                }
                else if (antParella.second == y) {
                    sols.insert(antParella.first);
                    parelles.erase(antParella);
                }
            }

            if (x < y) parelles.insert({x, y});
            else parelles.insert({y, x});

            if (not sols.empty()) {
                auto it2 = sols.find(x);
                if (it2 != sols.end()) sols.erase(x);
                it2 = sols.find(y);
                if (it2 != sols.end()) sols.erase(y);
            }
        }   
    }
}