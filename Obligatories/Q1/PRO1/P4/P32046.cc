#include <iostream>
using namespace std;

int main() {
    int n, m;
    int sum = 0;
    cin >> n;

    cout << "nombres que acaben igual que " << n 
    << ":" << endl;

    while (cin >> m) {
        if (m%1000 == n%1000) {
        cout << m << endl;
        ++sum;
        }
    }
    cout << "total: " << sum << endl;
    
}