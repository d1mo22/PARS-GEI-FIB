#include <iostream>
using namespace std;

struct Fraccio {
    int num, den;
};

Fraccio signe(Fraccio f) {
    if (f.den < 0) {
        f.den *= -1;
        f.num *= -1;
    }
    return f;
}

int mcd(int x, int y) {
    if(x < 0) x *= -1;
    if (y < 0) y *= -1;
    while (x != y) {
        if (x > y) x -=y;
        else y -= x;
    }
    return x;
}

Fraccio reduccio(Fraccio f) {
    int divisor = mcd(f.num, f.den);
    f.num /= divisor;
    f.den /= divisor;
    return signe(f);
}

Fraccio suma(const Fraccio& x, const Fraccio& y) {
    Fraccio resultat;
    resultat.num = x.num*y.den+y.num*x.den;
    resultat.den = x.den*y.den;
    return signe(reduccio(resultat));
}

Fraccio resta(const Fraccio& x, Fraccio& y) {
    y.num = -y.num;
    return suma(x, y);
}

Fraccio multiplicacio(const Fraccio& x, const Fraccio& y) {
    Fraccio resultat;
    resultat.num = x.num*y.num;
    resultat.den = x.den*y.den;
    return signe(reduccio(resultat));
}

Fraccio divisio(const Fraccio& x, const Fraccio& y) {
    Fraccio resultat;
    resultat.num = x.num*y.den;
    resultat.den = x.den*y.num;
    return signe(reduccio(resultat));
}

int main() {
    Fraccio resultat;
    string operador;
    cin >> resultat.num >> resultat.den;
    resultat = reduccio(resultat);
    cout << resultat.num << '/' << resultat .den << endl;
    while(cin >> operador) {
        Fraccio seguent;
        cin >> seguent.num >> seguent.den;
        if (operador == "suma") {
            resultat = suma(resultat, seguent);
        }
        else if (operador == "resta") {
            resultat = resta(resultat, seguent);
        }
        else if (operador == "multiplica") {
            resultat = multiplicacio(resultat, seguent);
        }
        else resultat = divisio(resultat, seguent);
        if (resultat.den == 1) cout << resultat.num << endl;
        else if (resultat.num == 0) cout << resultat.num << endl;
        else cout << resultat.num << "/" << resultat.den << endl;
    }
}