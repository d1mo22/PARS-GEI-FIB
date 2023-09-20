#include <iostream>
using namespace std;

int main() {
    int n;
    string a, b;
    int i = 0;
    int aux = 0;
    

    while (cin >> n) {
        bool order = true;

        if (n > 0) {
            cin >> a;
            for (int j = 0; j < n - 1; ++j) {
            cin >> b;
            if (b < a) order = false;
            a = b;
            }
        }
        ++i;
        if (order) aux = i;
    }
    if (aux != 0) cout << "The last line in increasing order is " <<
    aux << "." << endl;
    else cout << "There is no line in increasing order." << endl;
}