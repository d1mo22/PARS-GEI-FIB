#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int count = 1;
    int suma_p = 0;
    int suma_e = 0;

    for (int i = n; i > 0; i /= 10) {
        if (i%2 != 0) suma_e += n%10;

        else suma_p += n/10;
        n /= 10;
    }
    cout << suma_e << " " << suma_p << endl;
    
    if (suma_e == 0 or suma_p == 0) {
        
        if (suma_e > suma_p) {
            cout << suma_p << " = " << suma_p << " * " 
            << suma_e << endl;
        }

        else cout << suma_e << " = " << suma_e << " * " 
        << suma_p << endl;  
    } 
   
    else if (suma_e%suma_p == 0 or suma_p%suma_e == 0) {
        
        if (suma_e > suma_p) {
            cout << suma_e << " = " << suma_e/suma_p << " * " 
            << suma_p << endl;
        }

        else cout << suma_p << " = " << suma_p/suma_e << " * " 
        << suma_e << endl; 
    }
    
    else cout << "res" << endl;
    

}