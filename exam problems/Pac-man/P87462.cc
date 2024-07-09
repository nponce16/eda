#include <iostream>
#include <vector>
using namespace std;

typedef vector< vector<char> > Tauler;

bool near_to_F(const Tauler& T, int x, int y) {
    //arriba
    if (T[x+1][y] == 'F') return true;
    //abajo
    if (T[x-1][y] == 'F') return true;
    //izquierda
    if (T[x][y-1] == 'F') return true;
    //derecha
    if (T[x][y+1] == 'F') return true;
    //diag ArI
    if (T[x+1][y-1] == 'F') return true;
    //diag AbI
    if (T[x-1][y-1] == 'F') return true;
    //diag AbD
    if (T[x-1][y+1] == 'F') return true;
    //diag ArD
    if (T[x+1][y+1] == 'F') return true;
    
    return false;
}

bool bolet(Tauler& T, int x, int y) {
    if (T[x][y] == 'B' and not near_to_F(T,x,y)) return true;
    if (T[x][y] != 'X' and not near_to_F(T,x,y)) {
        T[x][y] = 'X';
        return bolet(T,x+1,y) or bolet(T,x,y+1) or bolet(T,x-1,y) or bolet(T,x,y-1);
    }
    return false;
}

int main() {
    int f, c;
    while (cin >> f >> c) {
        
        Tauler tauler(f, vector<char>(c));
        //leer
        int x0, y0;
        for (int i = 0; i < f; ++i) {
            for (int j = 0; j < c; ++j) {
                cin >> tauler[i][j];
                if (tauler[i][j] == 'P') {
                    x0 = i;
                    y0 = j;
                }
            }
        }
        if (bolet(tauler,x0,y0)) cout << "si" <<endl;
        else cout << "no" << endl;
    }
}