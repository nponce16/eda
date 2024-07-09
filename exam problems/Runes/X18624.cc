#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool is_vowel(char c) {
    return c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u';
}

void escriu(vector<char> v) {
    for (char c : v) cout << c;
    cout << endl;
}

void paraules(set<char> lletres, vector<char> parcial, int idx, int n, bool vocal) {
    if (idx == n) {
        escriu(parcial);
    }
    else {
        for (auto c : lletres) {
            if ((vocal and not is_vowel(c)) or not vocal) {
                parcial[idx] = c;
                paraules(lletres, parcial, idx + 1, n, is_vowel(c));
            }
        }
    }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        set<char> lletres;
        for (int i = 0; i < m; ++i) {
            char c;
            cin >> c;
            lletres.insert(c);
        }

        vector<char> parcial(n);
        paraules(lletres, parcial, 0, n, false);
        cout << string(10, '-') << endl;

    }
}