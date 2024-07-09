#include <iostream>
#include <set>
using namespace std;

int main() {
    int n;
    cin >> n;
    double qtt;
    string accion;
    long int valorMax = 0;
    set<int, greater<int>> valors; //guarda el valor de las joyas, menos el de las mas valiosas
    set<int> nMax; //guarda las n joyas de mayor valor

    while (cin >> accion >> qtt) {
        auto it_max = nMax.begin();

        if (accion == "deixar") {
            //si todavia hay espacio en la bolsa
            if (nMax.size() < n) {
                nMax.insert(qtt);
                valorMax += qtt;
            }
            else { //si no hay mas espacio
                if (qtt > (*it_max)) {  //hay que intercambiar
                    valorMax -= (*nMax.begin());
                    valors.insert(*nMax.begin());    //guardo el maximo de menor valor
                    nMax.erase(it_max);
                    nMax.insert(qtt);
                    valorMax += qtt;
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
                if (valors.begin() != valors.end()) {
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