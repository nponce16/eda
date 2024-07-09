#include <iostream>
#include <vector>
using namespace std;

//escribe el vector A
void write(vector<int> &A) {
    cout << '(' << A[0];
    for (int i = 1; i < A.size(); ++i) cout << ',' << A[i];
    cout << ')' << endl;
}

/**
 * A: vector de permutaciones, medida n
 * n: permutaciones de los numeros {1,2,...,n}
 * idx: primera casilla vacia de A
*/
void permutation(vector<int> &A, vector<bool> &used, int idx, int n) {
    if (idx == A.size()) write(A);
    else {
        for (int k = 1; k <= n; ++k) {
            if (not used[k]) {
                used[k] = 1;
                A[idx] = k;
                permutation(A, used, idx+1, n);
                used[k] = 0; //restauro -> backtrack
            }
        }
    }
}

int main() {
    int n; cin >> n;
    vector<int> A(n);
    vector<bool> used(n, 0);
    permutation(A, used, 0, n);
}