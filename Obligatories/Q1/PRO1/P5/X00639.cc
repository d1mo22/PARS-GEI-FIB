#include <iostream>
using namespace std;


bool c_frac(int n1, int d1, int n2, int d2) {
    double a, b;
    a = double(n1)/d1;
    b = double(n2)/d2;
    return a < b;
    
}


int main() {
    double n1, d1, n2, d2;
    while (cin >> n1 >>  d1 >> n2 >> d2) {
        if (c_frac(n1,d1,n2,d2)) cout << "yes" << endl;
        else cout << "no" << endl;
    }   
}
