#include <iostream>
using namespace std;

void convergeix(int n, int& k, int& lluny) {
    k = 0;
    lluny = 0;

    while(n != 1) {
        if (n%2 == 0) n /= 2;
        else n = 3*n + 1;

        if (n > lluny) lluny = n;
        ++k;
    }
}

int main() {
    int m, p;
    int k = 0;
    int lluny = 0;
    cin >> m >> p;
    int max = m;

    for (int i = 1; i < m + 1; ++i) {
        convergeix(i, k, lluny);
        if (lluny > max) max = lluny;
        if (k >= p) cout << i << endl;
    }
    cout << "S'arriba a " << max << "." << endl;
}