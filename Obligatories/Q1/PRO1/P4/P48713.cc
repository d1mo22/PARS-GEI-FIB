#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
    int seq; 
    int x = 2;
    cin >> seq;
    cout << seq;
    
    bool prim = true;

    while (x*x <= seq and prim) {
        if (seq%x == 0) prim = false;
        ++x;
    }

    if (seq < 2) cout << " is not prime" << endl;
    else if (prim) cout << " is prime" << endl;
    else cout << " is not prime" << endl;
    }
}