#include <iostream>
using namespace std;

// Introduir 2 numeros
// La suma dels cubs de a^3 + (a+1)^3 ... (b-1)^3+b^3

int main () {
    int a, b;
    int sum = 0;

    while (cin >> a >> b){
            for (int i = b; i >= a; --i){
            sum += i*i*i;
            }
        cout << "suma dels cubs entre " << a << " i " << b
        << ": " << sum << endl;
        sum = 0;     
    }
    
}
