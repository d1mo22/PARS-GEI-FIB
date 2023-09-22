#include <iostream>
using namespace std;

// x seguit d'una sequencia de numeros
// Quants d'aquesta sequencia son multiples de x

int main () {
    int x, a;
    cin >> x;

    int count = 0;
    while (cin >> a){
        if(a%x == 0) ++count;
    }
    cout << count << endl;
}