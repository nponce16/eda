#include <iostream>
#include <map>
using namespace std;


struct Info {
  string code;
  int price;
};


int main() {
  map<int, Info> M;
  char c;
  while (cin >> c) {

    if (c == 'n') {
      cout << "num: " << M.size() << endl;
    }
    else if (c == 'u') {
      string code;
      int length, price;
      cin >> code >> length >> price;
      M[length] = {code, price};
    }
    else if (c == 'q') {
      int length;
      cin >> length;
      map<int, Info>::const_iterator it = M.find(length);
      if (it != M.end()) cout << it->second.price << endl;
      else cout << -1 << endl;
    }
    else if (c == 'p') {
      cout << string(10, '-') << endl;
      map<int, Info>::const_iterator it = M.begin();
      while(it != M.end()) {
        cout << it->second.code << ' ' << it->first << ' ' << it->second.price << endl;
        ++it;
      }
      cout << string(10, '*') << endl;
    }
    else { // c == 's'
      map<int, Info>::const_iterator it = M.begin();
      ++it;
      if (it != M.end()) {
        cout << it->second.code << ' ' << it->first << ' ' << it->second.price << endl;
      }
      else cout << "no" << endl;
    }
  }
}
