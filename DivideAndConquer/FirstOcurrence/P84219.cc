#include <iostream>
#include <vector>
using namespace std;

int binary_search(const vector<double>& v, const double& x, int l, int r) {
    if (l > r) return -1;    //el elemento no esta
    int m = (l + r)/2; //punto medio

    if (x == v[m]) {
        if (v[m] == v[m-1]) return binary_search(v, x, l, m - 1);
        return m;
    }
    else if (x < v[m]) return binary_search(v, x, l, m - 1);
    else return binary_search(v, x, m + 1, r);
}

//pre: el vector esta ordenado crecientemente
int first_occurrence(double x, const vector<double>& v) {
    int size = v.size() - 1;
    return binary_search(v, x, 0, size);
}