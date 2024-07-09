#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

typedef vector <vector <int>> Graf;

void readGraf(Graf& G) {
    
}

list<int> topological_search(Graf& G) {
    int n = G.size();
    vector<int> ge(n, 0);

    //ge tiene la cantidad de precedencias del vértice u
    for (int u = 0; u < n; ++u) {
        for (int i = 0; i < G[u].size(); ++i) {
            ++ge[G[u][i]];
        }
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int u = 0; u < n; ++u) {
        if (ge[u] == 0) {
            pq.push(u); //agregar los vértices sin precedencias
        }
    }

    list<int> L;
    while (not pq.empty()) {
        int u = pq.top();
        pq.pop();
        L.push_back(u);
        
        //buscar un vertice i que tenga de precedencia a u
        for (int i = 0; i < G[u].size(); ++i) {
            int v = G[u][i];
            //si tiene solo una precedencia
            if (--ge[v] == 0) pq.push(v);
        }
    }
    return L;
}

int main() {
    int n, m;

    while (cin >> n >> m) {
        Graf G(n);
        int x, y;
        for (int k = 0; k < m; ++k) {
            cin >> x >> y;
            G[x].push_back(y);
        }

        list<int> L = topological_search(G);
        auto it = L.begin();
        bool first = true;
        while (it != L.end()) {
            if (not first) cout << ' ' << *it;
            else {
                cout << *it; 
                first = false;
            }
            ++it;
        }
        cout << endl;
    }
}