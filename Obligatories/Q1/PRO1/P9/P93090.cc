#include <iostream>
#include <typeinfo>
using namespace std;

struct Fraccio {
    int num, den;
};
int mcd(int x, int y) {
    while (x != y) {
        if (x > y) x -= y;
        else y -= x;
    }
    return x;
}

Fraccio racional(Fraccio f) {
  int divisor = mcd(f.num, f.den);
  f.num /= divisor;
  f.den /= divisor;
  return f;
}

Fraccio suma(const Fraccio& x, const Fraccio& y) {
    Fraccio resultat;
    resultat.num = x.num*y.den+y.num*x.den;
    resultat.den = x.den*y.den;
    return racional(resultat);
}

int main() {
    Fraccio x, y;
    char slash, operador;
    cin >> x.num >> slash >> x.den;
    while (cin >> operador and operador != '=') {
        cin >> y.num >> slash >> y.den;
        x = suma(x,y);
    }
    cout << x.num << '/' << x.den << endl;
}
