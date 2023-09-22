#include <iostream>
using namespace std;

int compara(int d1, int m1, int a1, int d2, int m2, int a2) {
    if (a1 == a2) {
        if (m1 == m2) {
            if (d1 == d2) return 0;
            if (d1 > d2) return 1;
            if (d1 < d2) return -1;
        }
        if (m1 > m2) return 1;
        if (m1 < m2) return -1;
    }
    if (a1 < a2) return -1;
    else return 1;
}

int main() {
    int d1, m1, a1, d2, m2, a2;
    char c;
    while (cin >> d1 >> c >> m1 >> c >> a1 >> d2 >> c >> m2 >> c >> a2) {
        int a = compara(d1, m1, a1, d2, m2, a2);
        if (a == 1) cout << "posterior" << endl;
        else if(a == 0) cout << "iguals" << endl;
        else cout << "anterior" << endl;
    }
}