#include <typeinfo>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


struct Estudiant {
    int dni;
    string nom;
    double nota;
    bool repetidor;
};

void informacio(const vector<Estudiant>& es, double& min, double& max, double& mitj) {
    max = mitj = 0;
    min = 10;
    int mida = es.size();
    int contador = 0;

    for (int i = 0; i < mida; ++i) {
        if (not es[i].repetidor and es[i].nota != -1) {
            if (es[i].nota > max) max = es[i].nota;
            if (es[i].nota < min) min = es[i].nota;       
            mitj += es[i].nota;
            ++contador;
        }
    }
    if (contador != 0) mitj = mitj/double(contador);
    else min = max = mitj = -1.0;
}
