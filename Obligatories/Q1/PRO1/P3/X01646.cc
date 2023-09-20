#include <iostream>
using namespace std;

int main () {
    int n, b, suma = 0;
    cin >> b;
    while (cin >> n){ 
        for (int i = n; i > 0; i = i/b){
            suma += i%b;
        }
        cout << n << ": " << suma << endl;
        suma = 0;
    }
}
 