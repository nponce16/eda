#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


int main() {
    string line;
    int count, max_count;
    set<int> sequence;

    while(getline(cin,line)) {      //lee el input hasta el salto de linea
        istringstream iss(line);        //stream de la linea leida
        int num;
        //Lee termino a termino la linea
        while(iss >> num) sequence.insert(num);
    }    
}

