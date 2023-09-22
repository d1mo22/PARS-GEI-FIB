#include <iostream>
using namespace std;

int main () {
    char m, n;
    cin >> m >> n;

    if (m == n) cout << "-" << endl;
    else if (m == 'V' and n == 'A') cout << "1" << endl;
    else if (m == 'A' and n == 'V') cout << "2" << endl;
    else if (m == 'A' and n == 'P') cout << "1" << endl;
    else if (m == 'P' and n == 'A') cout << "2" << endl;
    else if (m == 'V' and n == 'P') cout << "2" << endl;
    else if (m == 'P' and n == 'V') cout << "1" << endl;
}