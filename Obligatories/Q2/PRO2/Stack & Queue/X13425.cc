#include <iostream>
#include <queue>
#include "ParInt.hh"
#include "CuaIOParInt.hh"
using namespace std;

int main() {
    int t1 = 0, t2 = 0;
    queue<ParInt> cua;
    queue<ParInt> fila_1;
    queue<ParInt> fila_2;
    llegirCuaParInt(cua);

    while (not cua.empty()) {
        if (t2 < t1) {
            fila_2.push(cua.front());
            t2 += cua.front().segon();
        }
        else {
            fila_1.push(cua.front());
            t1 += cua.front().segon();
        }
        cua.pop();
    }
    escriureCuaParInt(fila_1);
    cout << endl;
    escriureCuaParInt(fila_2);
}