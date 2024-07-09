#include <iostream>
#include <string>
#include <vector>
using namespace std;


void write(const string& word) {
    
}

void merge_letters(int i, const string& cons, const string& vow, vector<char> cons_used, vector<char> vow_used, const string& word) {
    int n = cons.length();
    if (i == 2*n) cout << word << endl;
    else {
        if (i%2 == 0) {
            
        }
    }
}

int main() {
    int n;
    cin >> n;

    string cons, vow;
    cin >> cons >> vow;

    vector<char> cons_used(n);
    vector<char> vow_used(n);

    
}