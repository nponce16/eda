#include <iostream>
#include <vector>
using namespace std;

void escriu(vector<int> num) {
    for (int x : num) cout << x;
    cout << endl;
}

//mira si los prefijos (num) son multiplos de los divisores guardados en div
bool esMultiple(vector<int>& div, int num) {
    for (int i = 0; i < div.size(); ++i) {
        if (num%div[i] == 0) return true;
    }
    return false;
}

//retorna el numero guardado en v
int vectorNum(vector<int> v, int idx) {
    int num = 0;
    for (int i = 0; i <= idx; ++i) {
        num = num*10 + v[i];
    }
    return num;
}

void backtracking(int idx, int n, vector<int>& num, vector<int>& div) {
    if (idx == n) { //sol. parcial
        escriu(num);
    }
    else {
        int act_num;
        for (int k = 0; k <= 9; ++k) {
            num[idx] = k;   //pruebo los valores para v
            act_num = vectorNum(num, idx);
            //miro si los prefijos son multiples
            if (not esMultiple(div, act_num)) backtracking(idx+1, n, num, div);
        }
    }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<int> num(n);
        vector<int> divisor(m);
        for (int i = 0; i < m; ++i) cin >> divisor[i];

        backtracking(0, n, num, divisor);
        cout << "----------" << endl;
    }
}