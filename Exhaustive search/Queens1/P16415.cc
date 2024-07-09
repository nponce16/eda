#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> queens, diag1, diag2, col;


int nqueens(const int &i) {
    if (i == n) return 1;
    else {
        int res = 0;
        for (int j = 0; j < n; ++j) {
            if (col[j] == 0 and diag1[i+j] == 0 and diag2[(i-j) + (n-1)] == 0) {
                queens[i] = j;
                col[j] = diag1[i+j] = diag2[(i-j)+(n-1)] = 1;
                res += nqueens(i+1);
                col[j] = diag1[i+j] = diag2[(i-j)+(n-1)] = 0;
            }
        }
        return res;
    }
}


int main() {
    cin >> n;
    queens = vector<int> (n);
    diag1 = diag2 = vector<int>(2*n - 1, 0);
    col = vector<int> (n, 0);

    int i = 0;
    int sols= nqueens(i);
    cout << sols << endl;
}