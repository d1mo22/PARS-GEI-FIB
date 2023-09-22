#include <iostream>
using namespace std;

int main() {
    cout.setf(ios::fixed);
    cout.precision(4);

    double a, b, k;
    double suma = 0;
    
    while (cin >> a >> b >> k) {
        for (int i = 0; i < b; ++i){
            if ((a+(k*i)) <= b){
                suma += 1/(a+(k*i));
            }
        }
        cout << suma << endl;
        suma = 0;
    }
}