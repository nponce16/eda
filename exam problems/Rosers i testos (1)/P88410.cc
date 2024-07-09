#include <iostream>
#include <vector>
using namespace std;

void backtracking(int idx, int n, vector<int>& possibilitats, int uns, int dos, int tres, bool consecutiu, int ant) {
    if (idx == 3*n) {
        if (consecutiu and uns == n and dos == n and tres == n) {
            for (int x : possibilitats) cout << x;
            cout << endl;
        }
    }
    else {
        for (int k = 1; k <= 3; ++k) {
            if (not consecutiu or ant != k) {   //si no se repite el anterior y habia un consecutivo o si no hay consecutivos
                if (k == 1 and uns < n) {
                    possibilitats[idx] = k;
                    ++uns;
                    backtracking(idx + 1, n, possibilitats, uns, dos, tres, (ant == k  or consecutiu), k);
                    --uns;
                }
                if (k == 2 and dos < n) {
                    possibilitats[idx] = k;
                    ++dos;
                    backtracking(idx + 1, n, possibilitats, uns, dos, tres, (ant == k  or consecutiu), k);
                    --dos;
                }
                if (k == 3 and tres < n) {
                    possibilitats[idx] = k;
                    ++tres;
                    backtracking(idx + 1, n, possibilitats, uns, dos, tres, (ant == k  or consecutiu), k);
                    --tres;
                }
            }
        }
    }
}

int main() {
    int n;
    while (cin >> n) {
        vector<int> possibilitats(3*n);
        backtracking(0, n, possibilitats, 0, 0, 0, false, -1);
        cout << "**********" << endl;
    } 
}