#include <iostream>
using namespace std;

int main () {
    int n;
    bool even = false;
    int posicio = 1;
    while (not even and cin >> n){
        if (n%2 == 0) even = true;
        else ++posicio;
    }
    cout << posicio << endl;
}