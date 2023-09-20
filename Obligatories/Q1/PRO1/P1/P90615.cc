#include <iostream>
using namespace std;

//Quin dels tres numeros es més gran

int main () {
    int a, b, c;
    cin >> a >> b >> c;

    if (a >= b and  a >= c) {
        cout << a << endl;
    }
    else if (b >= a and b >= c) {
        cout << b << endl;
    }
    else {
        cout << c << endl;
    }
}