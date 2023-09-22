#include <iostream>
using namespace std;

// La suma dels digits impars si es par o impar

int main () {
    int x, sum = 0;
    cin >> x;

    for (int i = x; i > 0; i = i/100){
        sum += i%10;    
    }
    if (sum % 2 == 0){
        cout << x << " IS COOL" << endl;
    }
    else cout << x << " IS NOT COOL" << endl;

}