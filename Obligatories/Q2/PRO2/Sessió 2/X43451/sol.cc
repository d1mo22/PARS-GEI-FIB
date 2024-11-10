#include <iostream>
#include <vector>
#include "Estudiant.hh"

void arrodonir_vector(vector<Estudiant>& v) {
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        if (v[i].te_nota()) {
            double nota = v[i].consultar_nota();
            double nota_arrodonida = int((nota + 0.05) * 10) / 10.0;
            v[i].modificar_nota(nota_arrodonida);
        }
    }
}