#include <iostream>
using namespace std;

struct Fraccion {
    int num, den;
};

// Función que encuentra el máximo común divisor (MCD) de dos números
int mcd(int x, int y) {
    while (x != y) {
        if (x > y) x -= y;
        else y -= x;
    }
    return x;
}

// Función que reduce la fracción a su forma más simplificada
Fraccion reducir(Fraccion f) {
    int divisor = mcd(f.num, f.den);
    f.num /= divisor;
    f.den /= divisor;
    return f;
}

// Función que suma dos fracciones
Fraccion suma(Fraccion x, Fraccion y) {
    x.num = x.num * y.den + y.num * x.den;
    x.den = x.den * y.den;
    return reducir(x);
}

// Función que resta dos fracciones
Fraccion resta(Fraccion x, Fraccion y) {
    y.num = -y.num;
    return suma(x, y);
}

// Función que multiplica dos fracciones
Fraccion multiplicacion(Fraccion x, Fraccion y) {
    x.num *= y.num;
    x.den *= y.den;
    return reducir(x);
}

// Función que divide dos fracciones
Fraccion division(Fraccion x, Fraccion y) {
    swap(y.num, y.den);
    return multiplicacion(x, y);
}

int main() {
    Fraccion resultado;
    char op;
    cin >> resultado.num >> op >> resultado.den;
    cout << resultado.num << '/' << resultado.den << endl;
    while (cin >> op) {
        Fraccion siguiente;
        cin >> siguiente.num >> op >> siguiente.den;
        string operacion;
        cin >> operacion;
        if (operacion == "add") {
            resultado = suma(resultado, siguiente);
        } else if (operacion == "substract") {
            resultado = resta(resultado, siguiente);
        } else if (operacion == "multiply") {
            resultado = multiplicacion(resultado, siguiente);
        } else if (operacion == "divide") {
            resultado = division(resultado, siguiente);
        }
        cout << resultado.num << '/' << resultado.den << endl;
    }
    return 0;
}
