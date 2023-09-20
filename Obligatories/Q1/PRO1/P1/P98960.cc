#include <iostream>
using namespace std;

// Canvia una majuscula per una minuscula i viceversa

int main () {
    char c;
    cin >> c;

    if (c >= 'A' and c <= 'Z') {
        cout << char(c + 'a' - 'A') << endl;
    }
    else if (c >= 'a' and c <= 'z') {
        cout << char(c + 'A' - 'a') << endl;
    }
}