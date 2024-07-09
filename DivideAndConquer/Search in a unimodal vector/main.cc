#include <iostream>
#include <vector>
using namespace std;

int pic(const vector<int>& v, int l, int r) {
  if (l > r) return -1;
  int m = (l + r)/2;
  if (v[m-1] < v[m] and v[m] > v[m+1]) return m;
  if (v[m] < v[m+1]) return pic(v, m + 1, r);
  return pic(v, l, m - 1);
}

int binary_search_left(const vector<int>& v, int x, int l, int r) {
  if (l > r) return -1;
  int m = (l + r)/2;
  if (x < v[m]) return binary_search_left(v, x, m - 1, r);
  if (x > v[m]) return binary_search_left(v, x, l, m + 1);
  return m;
}

int binary_search_right(const vector<int>& v, int x, int l, int r) {
  if (l > r) return -1;
  int m = (l + r)/2;
  if (x > v[m]) return binary_search_right(v, x, m - 1, r);
  if (x < v[m]) return binary_search_right(v, x, l, m + 1);
  return m;
}

bool search(int x, const vector<int>& v) {
  int size = v.size() - 1;
  int top = pic(v, 0, size);
  int bin_esq = binary_search_left(v, x, 0, top);
  int bin_der = binary_search_right(v, x, top, size);
  if (x == v[bin_esq] or x == v[bin_der]) return true;
  return false;
}


int main() {
    int n;
    while (cin >> n) {
        vector<int> V(n);
        for (int i = 0; i < n; ++i) cin >> V[i];
        int m;
        cin >> m;
        while (m--) {
          int x;
          cin >> x;
          cout << ' ' << search(x, V);
        }
        cout << endl;
    }
}
