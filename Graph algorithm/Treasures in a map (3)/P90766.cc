#include <iostream>
#include <vector>
using namespace std;

typedef vector< vector<char> > M;

void leer_mapa(M& mapa, int n, int m) {
    for (int i = 1; i < n+1; ++i) {
        for (int j = 1; j < m+1; ++j) cin >> mapa[i][j];
    }
}

void found(M& mapa, M& visitados, int i, int j, int& count) {
    visitados[i][j] = '1';
    if (mapa[i][j] == 't') ++count;
    if (mapa[i-1][j] != 'X' and visitados[i-1][j] == '0') found(mapa, visitados, i-1, j, count);
    if (mapa[i+1][j] != 'X' and visitados[i+1][j] == '0') found(mapa, visitados, i+1, j, count);
    if (mapa[i][j-1] != 'X' and visitados[i][j-1] == '0') found(mapa, visitados, i, j-1, count);
    if (mapa[i][j+1] != 'X' and visitados[i][j+1] == '0') found(mapa, visitados, i, j+1, count);
}

int main() {
    int n, m;
    cin >> n >> m;
    M mapa(n+2, vector<char>(m+2, 'X'));
    M visitados(n+2, vector<char> (m+2, '0'));
    leer_mapa(mapa, n, m);

    int r, c;
    cin >> r >> c;
    int count = 0;
    found(mapa, visitados, r, c, count);
    cout << count << endl;
}