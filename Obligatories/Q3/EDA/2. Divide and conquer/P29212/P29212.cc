#include <iostream>
using namespace std;

int expo(int n, int k, int m) {
    if (k == 0) return 1;
    int y = expo(n, k/2, m);
    int z = (y*y)%m;
    if (k%2 == 0) return z;
    else return (z*n)%m;
}

int main() {
    int n, k, m;
    while (cin >> n >> k >> m) {
        cout << expo(n, k, m) << endl;
    }
}