#include <iostream>
#include <math.h>
using namespace std;

int main() {
    cout.setf(ios::fixed);
    cout.precision(4);

    double x, n;
    cin >> x;

    double sum = 0;
    int i = 0;

    while (cin >> n) {
        sum += n*pow(x, i);
        ++i;
    }
    cout << sum << endl;
}