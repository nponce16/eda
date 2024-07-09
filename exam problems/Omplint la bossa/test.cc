#include <iostream>
#include <set>
using namespace std;

int main() {
    int n;
    cin >> n;
    int qtt;
    string accion;
    long int valorMax = 0;
    set<int, greater<int>> valors; //guarda el valor de las joyas, menos el de las mas valiosas
    set<int> nMax; //guarda las n joyas de mayor valor

    while (cin >> accion >> qtt) {
        auto it_max = nMax.begin();

        if (accion == "deixar") {
            cout << "" << endl;
            //si todavia hay espacio en la bolsa
            if (nMax.size() < n) {
                cout << "1" << endl;
                nMax.insert(qtt);
                valorMax += qtt;
            }
            else { //si no hay mas espacio
                cout << "2" << endl;

                if (qtt > (*it_max)) {  //hay que intercambiar
                    cout << "3" << endl;

                    valorMax = valorMax - (*nMax.begin()) + qtt;
                    valors.insert(*nMax.begin());    //guardo el maximo de menor valor
                    nMax.erase(it_max);
                    nMax.insert(qtt);
                }
                else valors.insert(qtt);    //es menor que los maximos
            }
        }
        else {
            it_max = nMax.find(qtt);
            //si el valor que eliminamos esta dentro de los máximos
            if (it_max != nMax.end()) {
                valorMax -= qtt;
                nMax.erase(qtt);
                if (valors.size() >= n) {
                    nMax.insert(*valors.begin());
                    valorMax += (*valors.begin());
                    valors.erase(*valors.begin());
                }
            }
            else valors.erase(qtt);
        }
        cout.precision(0);
        cout << fixed << valorMax << endl;
    }
}