#include <iostream>
#include <list>
#include <vector>
using namespace std;

typedef vector< vector<int> > graph;

//DFS para encontrar un ciclo: u vértice actual y v vértice anterior
bool cycle (const graph& G, int u, vector<bool>& visited, int v) {
    bool ciclo;
    //si ya habíamos visitado este vértice --> hay un ciclo
    if (visited[u]) return true;
    else {
        visited[u] = true;
        ciclo = false;
        //recorro los vecinos
        for (int i = 0; i < G[u].size() and not ciclo; ++i) {
            int ad = G[u][i];
            if (ad != v) ciclo = cycle(G, ad, visited, u);
        }
    }
    return ciclo;
}

//Determina si el grafo es un bosque
int forest(const graph& G) {
    int num_arb = 0;
    int n = G.size();
    bool ciclo = false;
    vector<bool> visited(n, false);

    //recorro el grafo
    for (int i = 0; i < n and not ciclo; ++i) {
        if (not visited[i]) {
            //me fijo si hay un ciclo desde el vertice actual
            ciclo = cycle(G, i, visited, -1);
            if (not ciclo) ++num_arb;
        }
    }
    if (ciclo) return -1;
    return num_arb;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        graph G(n);
        int x, y;
        //relleno el grafo con sus adyacencias
        for (int i = 0; i < m; ++i) {
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        int num_arb = forest(G);
        if (num_arb == -1) cout << "no" << endl;
        else cout << num_arb << endl;
    }
}