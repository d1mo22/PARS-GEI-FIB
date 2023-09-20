#include <iostream>
using namespace std;

// Intervals entre 2 zones

int main () {
    int a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;

    cout << "[";
    if (a2 > a1) a1 = a2;
    if (b2 < b1) b1 = b2;
    if (b1 >= a1) cout << a1 << "," << b1;
    cout << "]" << endl;
    
}