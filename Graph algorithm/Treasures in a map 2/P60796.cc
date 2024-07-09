#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Mapa;
typedef vector<vector<int>> Visited; //matriz del mapa que marca las casillas visitadas

void llegir_mapa(Mapa& mapa, int n, int m) {
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) cin >> mapa[i][j];
    }
}

int tresor_proper(Mapa& mapa, int f, int c) {
    int n = mapa.size();
    int m = mapa[0].size();
    Visited visited(n, vector<int>(m, 0));

    queue<pair<pair<int,int>,int>> q;//queue <posicion, distancia>
    q.push({{f,c}, 0}); //añado el inicio

    while(not q.empty()) {
        int act_x = q.front().first.first;
        int act_y = q.front().first.second;
        int dist = q.front().second;
        visited[act_x][act_y] = 1; //posicion inicial
        q.pop();
    
        //recorremos los vecinos
        if (mapa[act_x + 1][act_y] != 'X' and visited[act_x + 1][act_y] == 0) {
            if (mapa[act_x + 1][act_y] == '.') q.push({{act_x + 1, act_y}, dist+1});
            else return dist+1;
        }
        if (mapa[act_x][act_y + 1] != 'X' and visited[act_x][act_y + 1] == 0) {
            if (mapa[act_x ][act_y + 1] == '.') q.push({{act_x, act_y + 1}, dist+1});
            else return dist+1;
        }
        if (mapa[act_x - 1][act_y] != 'X' and visited[act_x -1][act_y] == 0) {
            if (mapa[act_x - 1][act_y] == '.') q.push({{act_x - 1, act_y}, dist+1});
            else return dist+1;
        }
        if (mapa[act_x][act_y - 1] != 'X' and visited[act_x][act_y - 1] == 0) {
            if (mapa[act_x][act_y - 1] == '.') q.push({{act_x, act_y - 1}, dist+1});
            else return dist+1;
        }
    }
    return -1;
}

int main() {
    int n, m;
    cin >> n >> m;
    Mapa mapa(n+2, vector<char>(m+2, 'X'));
    llegir_mapa(mapa, n, m);

    int f, c;
    cin >> f >> c;

    int minDistance = tresor_proper(mapa, f, c);
    if (minDistance != -1) cout << "distancia minima: " << minDistance << endl;
    else cout << "no es pot arribar a cap tresor" << endl;
}