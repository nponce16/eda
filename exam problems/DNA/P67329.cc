#include <iostream>
#include <vector>
using namespace std;

void nCombinations(vector<char> &letters,vector<char> &par, int n, int idx) {
    if (idx == n) {  //sol. parcial
        for (char c : par) cout << c;
        cout << endl;
    }
    else {
        for (int i = 0; i < letters.size(); ++i) {
            par[idx] = letters[i];
            nCombinations(letters, par, n, idx+1);
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<char> par(n);
    vector<char> letters = {'A', 'C', 'G', 'T'};
    nCombinations(letters, par, n, 0);
}