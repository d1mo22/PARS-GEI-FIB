#include <iostream>
using namespace std;

bool is_palindromic(int n) {
    int x, aux = 0;
    x = n;
    while (x != 0) {
        aux = aux*10 + x%10;
        x /= 10;
    }
    return n == aux;
};


int main() {
    int n;
    while (cin >> n) cout << (is_palindromic(n) ? "true" : "false") << endl;
}
