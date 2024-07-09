#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    cout.setf(ios::fixed);
    cout.precision(4);
    map<int, int> seq;      //map<numero, apariciones en la secuencia>
    int num;
    double size = 0;
    int suma = 0;
    string order;
    map<int, int>::iterator it;
    while(cin >> order) {
        if (order == "number") {
            cin >> num;
            it = seq.find(num);
            if(it != seq.end()) ++(it->second);     //si esta en el mapa, sumar las apariciones
            else seq.insert({num,1});               //si no esta, agregarlo
            suma += num;
            ++size;
        }
        else if (order == "delete" and not seq.empty()) {
            it = seq.begin();
            suma -= it->first;
            if (it->second == 1) seq.erase(it);     //si hay un solo elemento borrarlo
            else --(it->second);                    //si no, restar una aparicion
            --size;
        }
        if (seq.empty()) cout << "no elements" << endl;
        else {
            it = seq.begin();
            cout << "minimum: " << it->first;
            it = seq.end();
            --it;
            cout << ", maximum: " << it->first;
            cout << ", average: " << suma/size << endl;
        }
    }
}