#include <iostream>
using namespace std;

void print_digit(int n) {
    if (n < 10) cout << n;
    else cout << char(n - 10 + 'A');
}

void change_base(int n, int base) {
    if (n < base) print_digit(n);
    else {
        change_base(n/base, base);
        print_digit(n%base);
    }
}

int main() {
    int n;

    while (cin >> n) {
        cout << n << " = ";
        change_base(n, 2);
        cout << ", ";
        change_base(n, 8);
        cout << ", ";
        change_base(n, 16);
        cout << endl;
    }
}