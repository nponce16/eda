#include <iostream>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

typedef vector< vector <pair<int,int> > > Graf; // Graf: <(vertice u, vertice v), coste>

int dijkstra(Graf& graf, int x, int y) {
    vector<int> visited(graf.size(), 0);
    vector<int> dist(graf.size(), INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    pq.push({0, x});
    dist[x] = 0;

    while (not pq.empty())
    {
        int u = pq.top().second;
        int c_act = pq.top().first;
        pq.pop();

        if (not visited[u]) {
            visited[u] = 1;

            //miro los vecinos
            for (int i = 0; i < graf[u].size(); ++i) {
                int v = graf[u][i].second;
                int c = graf[u][i].first;
                if (dist[v] > c_act + c) {
                    dist[v] = c_act + c;
                    pq.push({dist[v], v});      //guardo las distancias para llegar de x a v
                }
            }
        }
    }

    //obtener distancia
    return dist[y];
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Graf graf(n);

        //lee el grafo
        for (int i = 0; i < m; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            graf[u].push_back({c,v});
        }

        int x, y;
        cin >> x >> y;

        int distance = dijkstra(graf, x, y);
        if (distance == INT_MAX) cout << "no path from " << x << " to " << y << endl;
        else cout << distance << endl;
    }
}