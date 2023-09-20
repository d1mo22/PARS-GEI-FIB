#include <iostream>
using namespace std;

double factorial(int n) {
    if (n == 0) return 1;
    return n*factorial(n - 1);
}

double taylor(int n) {
    double contador = 0;
    for (int i = 0; i < n; ++i) {
        contador += double(1/factorial(i));
    }
    return contador;
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(10);
    int n;
    while(cin >> n) {
        cout << "Amb " << n << " terme(s) s'obte " << taylor(n) << "." << endl;
    }
}