#include <iostream>
using namespace std;

int power(uint n, uint k, uint m) {     //retorna n^k
    if (k == 0) return 1;
    int x = power(n, k/2, m);
    if (k % 2 == 0) return x%m * x%m;
    return x%m * x%m * n%m;
}

int main() {
    uint n, k, m;
    while (cin >> n) {
        cin >> k >> m;
        cout << power(n, k, m) % m << endl;
    }
}