#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> queens, diag1, diag2, col;


void write() {
    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (queens[i] == j) cout << 'Q';
            else cout << '.';
        }
        cout << endl;
    }
}

bool nqueens(const int &i) {
    if (i == n) {
        return true;
    }
    else {
        int res = 0;
        for (int j = 0; j < n; ++j) {
            if (col[j] == 0 and diag1[i+j] == 0 and diag2[(i-j) + (n-1)] == 0) {
                queens[i] = j;
                col[j] = diag1[i+j] = diag2[(i-j)+(n-1)] = 1;
                if (nqueens(i+1)) return true;
                col[j] = diag1[i+j] = diag2[(i-j)+(n-1)] = 0;
            }
        }
        return false;
    }
}


int main() {
    cin >> n;
    queens = vector<int> (n);
    diag1 = diag2 = vector<int>(2*n - 1, 0);
    col = vector<int> (n, 0);

    bool sol = nqueens(0);
    if (sol) write();
    else cout << "NO SOLUTION" << endl;
}