#include <iostream>
using namespace std;

int main () {
    cout.setf(ios::fixed);
    cout.precision(10);

    double n, m;
    double sum = 0;
    while (cin >> n >> m){
        while (m < n){            
            ++m;
            sum += 1/m;
        }
        cout << sum << endl;
        sum = 0;
    }
}