#include <iostream>
#include <string>
using namespace std;

// Quina paraula té més valor en char

int main () {
    string a, b;
    cin >> a >> b;

    cout << a;
    if (a < b) cout << " < ";
    else if (a > b) cout << " > ";
    else cout << " = ";
    cout << b << endl;
}