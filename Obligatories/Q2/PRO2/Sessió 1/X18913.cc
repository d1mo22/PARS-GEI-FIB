#include <iostream>
using namespace std;
#include "vectorIOint.hh"

/* Buscar  */ 
/* Pre: cierto */
/* Post: si el resultado es v.size(), x no esta en v;
en caso contrario, indica la posicion de la primera aparicion de x en v */  
int busqueda_lin(const vector<int>& v, int x) {
  int tam = v.size();
  int i = 0;
  while (i < tam and v[i] != x) {
    ++i;
  }
  return i;
}

/*int main() {
  vector<int> v;
  leer_vector_int(v); 
  cout << "Escribe el elemento a buscar: " << endl;
  int x;
  cin >> x; 
  int b = busqueda_lin(v,x);
  cout << b << endl;
}*/