#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Prat;
typedef vector<vector<int>> Visited;
typedef pair<int,int> Pos;

vector<int> go_to_flors(Prat& prat, int x, int y) {
    queue<pair<Pos, int>> q; //q: <posicion, distancia
    vector<int> distancias; //distancias a flores
    Visited visited(prat.size(), vector<int>(prat[0].size(),0));

    q.push({{x,y}, {0}});
    visited[x][y] = 1;

    while(not q.empty()) {
        int act_x = q.front().first.first;
        int act_y = q.front().first.second;
        int act_dist = q.front().second;
        q.pop();

        if (prat[act_x + 2][act_y + 1] != 'a' and not visited[act_x + 2][act_y + 1]) {
            visited[act_x + 2][act_y + 1] = 1;
            q.push({{act_x+2,act_y+1},act_dist+1});

            if (prat[act_x + 2][act_y + 1] == 'F') {
                distancias.push_back(act_dist+1);
            }
        }
        if (prat[act_x + 2][act_y - 1] != 'a' and not visited[act_x + 2][act_y - 1]) {
            visited[act_x + 2][act_y - 1] = 1;
            q.push({{act_x + 2,act_y - 1},act_dist+1});

            if (prat[act_x + 2][act_y - 1] == 'F') {
                distancias.push_back(act_dist+1);
            }
        }
        if (prat[act_x - 2][act_y + 1] != 'a' and not visited[act_x - 2][act_y + 1]) {
            visited[act_x - 2][act_y + 1] = 1;
            q.push({{act_x - 2,act_y + 1},act_dist+1});

            if (prat[act_x - 2][act_y + 1] == 'F') {
                distancias.push_back(act_dist+1);
            }
        }
        if (prat[act_x - 2][act_y - 1] != 'a' and not visited[act_x - 2][act_y - 1]) {
            visited[act_x - 2][act_y - 1] = 1;
            q.push({{act_x - 2,act_y - 1},act_dist+1});

            if (prat[act_x - 2][act_y - 1] == 'F') {
                distancias.push_back(act_dist+1);
            }
        }
        if (prat[act_x + 1][act_y + 2] != 'a' and not visited[act_x + 1][act_y + 2]) {
            visited[act_x + 1][act_y + 2] = 1;
            q.push({{act_x+1,act_y+2},act_dist+1});

            if (prat[act_x + 1][act_y + 2] == 'F') {
                distancias.push_back(act_dist+1);
            }
        }
        if (prat[act_x - 1][act_y + 2] != 'a' and not visited[act_x - 1][act_y + 2]) {
            visited[act_x - 1][act_y + 2] = 1;
            q.push({{act_x-1,act_y+2},act_dist+1});

            if (prat[act_x - 1][act_y + 2] == 'F') {
                distancias.push_back(act_dist+1);
            }
        }
        if (prat[act_x + 1][act_y - 2] != 'a' and not visited[act_x + 1][act_y - 2]) {
            visited[act_x + 1][act_y - 2] = 1;
            q.push({{act_x+1,act_y-2},act_dist+1});

            if (prat[act_x + 1][act_y - 2] == 'F') {
                distancias.push_back(act_dist+1);
            }
        }
        if (prat[act_x - 1][act_y - 2] != 'a' and not visited[act_x - 1][act_y - 2]) {
            visited[act_x - 1][act_y - 2] = 1;
            q.push({{act_x-1,act_y-2},act_dist+1});

            if (prat[act_x - 1][act_y - 2] == 'F') {
                distancias.push_back(act_dist+1);
            }
        }

    }
    return distancias;
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(4);

    int n, m;
    cin >> n >> m;
    Prat prat(n+4, vector<char>(m+4, 'a'));
    int x0, y0;

    for (int i = 2; i < n+2; ++i) {
        for (int j = 2; j < m+2; ++j) {
            cin >> prat[i][j];
            if (prat[i][j] == 'C') {
                x0 = i;
                y0 = j;
            }
        }
    }

    vector<int> dist_flors = go_to_flors(prat, x0, y0);
    if (dist_flors.size() == 0) cout << "el cavall no pot arribar a cap flor" << endl;
    else {
        cout << "flors accessibles: " << dist_flors.size() << endl;

        int mitjana;
        for (int x : dist_flors) mitjana += x;

        cout << "distancia mitjana: " << (double)mitjana/dist_flors.size() << endl;
    }
}