#include <iostream>
using namespace std;

// un numero n
// el factorial del numero

int main () {
    int n, m = 1, sum = 0; 
    cin >> n;

    while (m <= n){      
        sum += (m * m);
        ++m;
    }

    cout << sum << endl;
}