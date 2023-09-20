#include <iostream>
using namespace std;



int main () {
    int n; 
    double sum = 0, m = 1;
    cin >> n;
    while (m <= n){
        sum += 1/m;
        ++m;
    }
    cout.setf(ios::fixed);
    cout.precision(4);
    cout << sum << endl;
}