#include <iostream>
#include <list>
#include "LlistaIOParInt.hh"
#include "ParInt.hh"
using namespace std;

void Calcular(list<ParInt>& l, int& p, int& suma, int& n) {
    p = 0;
    suma = 0;
    list<ParInt>::const_iterator it;
    for (it = l.begin(); it != l.end(); ++it) {
        ParInt a = *it;
        if (a.primer() == n) {
            ++p;
            suma += a.segon();
        }
    }
}

int main() {
    list<ParInt> l;
    int n, p, suma;
    LlegirLlistaParInt(l);
    cin >> n;
    Calcular(l, p, suma, n);
    cout << n << " " << p << " " << suma << endl;
}