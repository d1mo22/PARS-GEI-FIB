#include <iostream>
using namespace std;

/* Interval, dona el interval entre els 2 i diu quin
   esta a sobre de cada un, si son iguals o error */

int main () {
    int a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;

    if (a1 == a2 and b1 == b2){ 
        cout << "=";
    }
    else if (a1 >= a2 and b2 >= b1) {
        cout << "1";
    }
    else if (a1 <= a2 and b2 <= b1){
        cout << "2";
    } 
    else cout << "?";

    cout << " , ";

    cout << "[";
    if (a2 > a1) a1 = a2;
    if (b2 < b1) b1 = b2;
    if (b1 >= a1) cout << a1 << "," << b1;
    cout << "]" << endl;
}