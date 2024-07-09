#include <iostream>
#include <vector>
using namespace std;

//escribe el vector A
void write(vector<int> &A) {
    cout << A[0];
    for (int i = 1; i < A.size(); ++i) cout << ' ' << A[i];
    cout << endl;
}

/**
 * A: vector de medida n
 * idx: primera casilla no completa de A
 * k: numero total de 1s
*/
void cadenes(vector<int> &A, int idx, int k, int u, int z) {
    //caso base
    if (idx == A.size()) write(A);
    else {
        //poda1
        if (z < A.size() - k) { //faltan 0s
            A[idx] = 0;
            cadenes(A, idx+1, k, u, z+1);
        }
        //poda2
        if (u < k) { //faltan 1s
            A[idx] = 1;
            cadenes(A, idx+1, k, u+1, z);
        }
    }
}


int main() {
    int n, o;
    cin >> n >> o;
    vector<int> A(n);
    cadenes(A, 0, o, 0, 0);
}