#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector <vector<int>> Graf;

int mes_allunyat(Graf& G, int n) {
    vector<int> visitats(n, 0);
    queue<pair<int,int>> q; // q: <vertex, distancia>
    int max_dist = 0;
    int v_llunya = 0;

    q.push({0,0});
    visitats[0] = 1;

    while(not q.empty()) {
        int u = q.front().first;
        int act_dist = q.front().second;
        q.pop();
    
        //si esta vacia el ultimo elemento que visitamos es el de mayor distancia
        if (act_dist > max_dist)
        {
            max_dist = act_dist;
            v_llunya = u;
        }
        else if (act_dist == max_dist and u < v_llunya) v_llunya = u;
        
        //visito los vecinos
        for (int v : G[u]) {
            if (not visitats[v])
            {
                visitats[v] = 1;
                q.push({v, act_dist+1});
            }
            
        }
    }
    return v_llunya;
}

int main() {
    int n, m;
    while (cin >> n >> m) 
    {
        Graf G(n);

        for (int u = 0; u < m; ++u) {
            int x, y;
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }

        int vertex = mes_allunyat(G, n);
        cout << vertex << endl;
    }
}