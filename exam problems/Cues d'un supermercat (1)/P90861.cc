#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <queue>
using namespace std;

void llegirCues(map <int, queue<string>>& cues, int n) {
    string client;
    for (int i = 0; i <= n; ++i) {
        queue<string> clients;
        string line;

        getline(cin, line);
        istringstream iss(line);
        string client;
        while(iss >> client) {
            clients.push(client);
        }
        
        if (i > 0) cues.insert({i, clients});
    }
}

void escriureSortides(queue<string>& sortides) {
    cout << "SORTIDES" << endl;
    cout << "--------" << endl;

    while (not sortides.empty()) {
        cout << sortides.front() << endl;
        sortides.pop();
    }

}

void escriureContinguts(map<int, queue<string>>& cues) {
    cout << "CONTINGUTS FINALS" << endl;
    cout << "-----------------" << endl;

    auto it = cues.begin();
    while (it != cues.end()) {
        cout << "cua " << it->first << ':';
        while (not it->second.empty()) {
            cout << ' ' << it->second.front();
            it->second.pop();
        }
        cout << endl;
        ++it;
    }
}

int main() {
    int n;
    cin >> n;
    map <int, queue<string>> cues;
    llegirCues(cues, n);
    queue<string> sortides;

    string succes;
    while (cin >> succes) {
        int cua;
  
        if (succes == "SURT") { //un client surt de la cua
            cin >> cua;
            if (cua <= n and cua >= 1) {
                auto it = cues.find(cua);
                if (not it->second.empty()) {   //si hay clientes en la cola
                    sortides.push(it->second.front());
                    it->second.pop();
                }
            }
        }
        else { //un client entra a la cua
            string client;
            cin >> client >> cua;
            if (cua <= n and cua >= 1) {
                auto it = cues.find(cua);
                it->second.push(client);
            }
        }
    }

    escriureSortides(sortides);
    cout << endl;
    escriureContinguts(cues);

}