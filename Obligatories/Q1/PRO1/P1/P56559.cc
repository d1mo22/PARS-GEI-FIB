#include <iostream>
using namespace std;

/* Interval entre 2 zones i diu si es igual
 el primer sobre el segon, el segon sobre el primer
  o error*/

int main () {
    int a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;

    if (a1 == a2 and b1 == b2){ 
        cout << "=" << endl;
    }
    else if (a1 >= a2 and b2 >= b1) {
        cout << "1" << endl;
    }
    else if (a1 <= a2 and b2 <= b1){
        cout << "2" << endl;
    } 
    else cout << "?" << endl;
    
}
