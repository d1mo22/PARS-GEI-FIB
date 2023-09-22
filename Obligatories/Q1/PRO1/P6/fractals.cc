#include <iostream>
using namespace std;

void print_line(int n, char c) {
    for (int i = 0; i < n; ++i) cout << c;
    cout << endl;
}

void bars(int n) {
    if (n == 1) print_line(n,'*');
    else {
        bars(n - 1);
        print_line(n, '*');
        bars(n - 1);
    }
}

int main() {
    int n;
    cin >> n;
    bars(n);
}