#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n) {

        int p = n/7;
        n %= 7;

        while (n%4 != 0) {

            --p;
            n += 7;
        }
        cout << p << " " << n/4 << endl;
    }
}