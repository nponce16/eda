#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> Letters;

void backtracking(Letters& L, vector<char>& path, int act_x, int act_y, int xf, int yf) {
    if (act_x == xf and act_y == yf) {
        for (char c : path) cout << c;
        cout << endl;
    }
    else {
        char act_letter;

        if (L[act_x + 1][act_y] != '.') {
            act_letter = L[act_x+1][act_y];
            path.push_back(act_letter);
            L[act_x+1][act_y] = '.';
            backtracking(L, path, act_x+1, act_y, xf, yf);
            
            L[act_x+1][act_y] = path.back();
            path.pop_back();
        }
        if (L[act_x - 1][act_y] != '.') {
            act_letter = L[act_x - 1][act_y];
            path.push_back(act_letter);
            L[act_x - 1][act_y] = '.';
            backtracking(L, path, act_x - 1, act_y, xf, yf);
            
            L[act_x - 1][act_y] = path.back();
            path.pop_back();
        }
        if (L[act_x][act_y + 1] != '.') {
            act_letter = L[act_x][act_y + 1];
            path.push_back(act_letter);
            L[act_x][act_y + 1] = '.';
            backtracking(L, path, act_x, act_y + 1, xf, yf);
            
            L[act_x][act_y + 1] = path.back();
            path.pop_back();
        }
        if (L[act_x][act_y - 1] != '.') {
            act_letter = L[act_x][act_y - 1];
            path.push_back(act_letter);
            L[act_x][act_y - 1] = '.';
            backtracking(L, path, act_x, act_y - 1, xf, yf);
            
            L[act_x][act_y - 1] = path.back();
            path.pop_back();
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    Letters L(n+2, vector<char>(m+2, '.'));

    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) cin >> L[i][j];
    }

    int x0, y0, xf, yf;
    cin >> x0 >> y0 >> xf >> yf;
    vector<char> path;

    path.push_back(L[x0+1][y0+1]);
    L[x0+1][y0+1] = '.';
    backtracking(L, path, x0+1, y0+1, xf+1, yf+1);
}