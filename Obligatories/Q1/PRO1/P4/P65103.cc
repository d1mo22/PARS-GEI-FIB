#include <iostream>
using namespace std;

int main() {
    int i;
    cin >> i;
    int n = 1;
    int x;
    while (n <= i and cin >> x)++n;
    
    if (n == i + 1 and i != 0) {
        cout << "At the position " << i << " there is a(n) " 
        << x << "." << endl;
    }
    else cout << "Incorrect position." << endl;
}