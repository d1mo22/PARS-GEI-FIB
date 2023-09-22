#include <iostream>
using namespace std;

int main () {
    int n, m, sum = 1;
    cin >> n;
    m = n;

    while (m/10 != 0){   
        m = m/10;
        ++sum;       
    }
    cout << "The number of digits of " << n 
    << " is " << sum << "." << endl;
}