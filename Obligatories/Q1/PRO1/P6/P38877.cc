#include <iostream>
using namespace std;

void inverse(int n, int& i) {
    string c;
    if (cin >> c) {
        inverse(n, i);
        if (i <= n) {
            cout << c << endl;
            ++i;
        }
    }
    else i = 1;
}

int main() {
    int n;
    cin >> n;
    inverse(n, n);
}