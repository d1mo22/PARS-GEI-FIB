#include <iostream>
using namespace std;

bool prime(int n) {
    int i = 2;
    if (n == 1 or n == 0) return false;

    while (i*i <= n) {
        if (n%i == 0) return false;
        ++i;
    }
    return true;
}

int next_prime(int n) {
    int m = n + 1;
    while (not prime(m)) ++m;
    return m;
}

int main() {
    int n;
    while (cin >> n and prime(n)) {
        cout << next_prime(n) << endl;
    }
}