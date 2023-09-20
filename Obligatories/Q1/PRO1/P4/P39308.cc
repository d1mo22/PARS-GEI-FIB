#include <iostream>
using namespace std;

int main() {
    int n;

    while (cin >> n) {
        cout << "divisors of " << n << ":";
        int i = 1;
        while (i*i <= n) {
            if (n%i == 0) cout << " " << i;
            ++i;
        }
        --i;

        if (i*i == n) --i;

        while (i > 0) {
            if (n%i == 0) cout << " " << n/i;
            --i;
        }

        cout << endl;
    }
}