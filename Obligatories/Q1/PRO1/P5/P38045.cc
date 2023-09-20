#include <iostream>
#include <cmath>
using namespace std;

int square (int n){
    return n*n;
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(6);
    
    int n;
    while (cin >> n) {
        cout << square(n) << " " << sqrt(n) << endl;
    }
}