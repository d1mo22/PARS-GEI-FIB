#include <iostream>
using namespace std;

void que_paraula_es(int& contador_paraula, int& contador_p, int& contador_m, int& contador_g) {
    if (contador_paraula > 9) ++contador_g;
    else if (contador_paraula <= 9 and contador_paraula >= 5) ++contador_m;
    else if (contador_paraula != 0 and contador_paraula < 5) ++contador_p;
    contador_paraula = 0;
}

int main() {
    char c;
    int contador_p, contador_m, contador_g;
    contador_p = contador_m = contador_g = 0;
    int contador_paraula = 0;
    cin >> c;

    while (c != '.') {
      if (c == '-') que_paraula_es(contador_paraula, contador_p, contador_m, contador_g);
      else if (c != '-') ++contador_paraula;
      cin >> c;
    }
    que_paraula_es(contador_paraula, contador_p, contador_m, contador_g);
    //cout << contador_p << "," << contador_m << "," << contador_g << endl;
}