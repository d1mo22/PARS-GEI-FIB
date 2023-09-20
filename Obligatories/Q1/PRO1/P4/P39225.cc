#include <iostream>
using namespace std;

int main() {
    int i, x;
    cin >> i;

    for (int n = 0; n < i; ++n){
        cin >> x;
    }
    cout << "At the position " << i << " there is a(n) " 
    << x << "." << endl;
}