#include <iostream>
using namespace std;

int main () {
    int n, suma = 0;

    while (cin >> n){ 
        for (int i = n; i > 0; i = i/10){
            suma += i%10;
        }
        cout << "The sum of the digits of " << n << " is " << suma << "." << endl;
        suma = 0;
    }
}
    