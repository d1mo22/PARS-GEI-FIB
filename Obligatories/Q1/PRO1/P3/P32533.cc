#include <iostream>
using namespace std;

int main () {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            // si la suma de i+j es igual a n-1 posem un /
            if ((i+j) == (n-1)) cout << "/";
            // si la suma de i+j es menor a n-1 posem +
            else if ((i+j) < (n-1)) cout << "+";
            // si la suma de i+j es major a n-1 posem *
            else cout << "*";
        }
        cout << endl;
    }
    // al acabar el primer bucle el valor de i y j 
    // incrementa en 1 i repeteix el bucle
    
}