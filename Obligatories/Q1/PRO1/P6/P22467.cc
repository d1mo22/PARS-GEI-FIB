#include <iostream>
using namespace std;

int sum_of_digits(int n) {
    int sum = 0;
    for (int i = n; i != 0; i /= 10) {
        sum += i%10;
    }
    return sum;
}

bool prime(int n) {
    for (int i = 2; i*i <= n; ++i) {
        if (n%i == 0) return false;
    }
    return true;
}

bool is_perfect_prime(int n) {
    if (n == 2 or n == 3 or n == 5 or n == 7) return true;
    if (not prime(n)) return false;
    if (n == 0 or n == 1) return false;
    return is_perfect_prime(sum_of_digits(n));
}


int main() {
    int n;
    while (cin >> n) cout << (is_perfect_prime(n) ? "true" : "false") << endl;
}
