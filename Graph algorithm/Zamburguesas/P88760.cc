#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

typedef pair<pair<double, double>, double> circ; //P(x,y) amb radi r -> pair< <x,y>, r>  

int bfs(const vector<circ>& C, int d, int jumps) {
    int size = C.size();

    if (distance <= d) jumps = 1;
    else {
        queue<int> q;
        vector<bool> vis(size, false);
        vector<int> dist(size, INF);
        dist[0] = 0;
        for (int i = 0; i < size; ++i) {
            q.push(C[0]);
            
            int x = C[0].first.first - C[i].first.first;
            int y = C[0].first.second - C[i].first.second;
            int distance = sqrt(x*x + y*y) - C[0].second - C[i].second;
            if (distance <= d) q.push(i);

            while (not q.empty()) {
                int u = q.front();
                q.pop();
                if (not v[u]) {
                    vis[u] = true;
                    
                }
            }
        }
    }
    return jumps;

}

int main() {
    int n;
    double d;

    while (cin >> n >> d) {
        double x, y, r;
        vector <circ> C(n);
        for(int i = 0; i < n; ++i) cin >> C[i].first.first >> C[i].first.second >> C[i].second;


    }
}