#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main() {
    string s;
    vector<string> vec;
    int size;
    cin >> s;
    while (s != "END") {
        vec.push_back(s);
        sort(vec.begin(), vec.end());
        size = vec.size();
        if (size == 1) cout << vec[0] << endl;
        else {
            int med = (size - 1)/2;
            cout << vec[med] << endl;
        }
        cin >> s;
    }
}