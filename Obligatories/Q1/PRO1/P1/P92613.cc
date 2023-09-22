#include <iostream>
using namespace std;

//Dona el valor arodonit cap a baix, cap a dalt i el valor arrodonit

int main () {
    double x;
    cin >> x;

    int b = (int) x; 
    if (x == b) cout << b << " " << b << " " << b << endl;
    else cout << b << " " << b + 1 << " " << int(x + 0.5) << endl;
}