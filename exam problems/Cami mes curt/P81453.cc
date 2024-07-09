#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

typedef vector< set < int > > Graf;

vector<int> cami(const Graf& G, int v0, int vn) {
    vector<int> visited(G.size(), 0);
    queue< pair<int, vector<int>> > q;   //cola con el vertice actual y el camino hacia el
    
    q.push({v0, {0}});
    visited[v0] = 1;

    while(not q.empty()) {
        int u = q.front().first;
        vector<int> path = q.front().second;
        q.pop();

        //si no llegue al final
        if (u != vn) {
            for (int i : G[u]) {
                if (not visited[i]) {
                    visited[i] = 1;
                    //auxiliar para no cambiar el path
                    vector<int> new_path = path;
                    new_path.push_back(i);
                    q.push({i, new_path});
                    
                }
            }
        }
        else return path;
    }
    return {-1};
}

int main() {
    int n, m;
    while(cin >> n >> m) {
        Graf G(n);

        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            G[x].insert(y);
        }
        vector<int> best_path = cami(G, 0, n-1);
        
        cout << best_path[0];
        for (int i = 1; i < best_path.size(); ++i) cout << ' ' << best_path[i];
        cout << endl;
    }
}