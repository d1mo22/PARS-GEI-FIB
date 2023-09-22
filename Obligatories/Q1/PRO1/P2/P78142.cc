#include <iostream>
using namespace std;

int main () {
    cout.setf(ios::fixed);
    cout.precision(2); 
    double x, suma = 0, count = 0;

    while (cin >> x){
        suma = suma + x;
        ++count;
        
    }
    cout << (suma/count) << endl;
}