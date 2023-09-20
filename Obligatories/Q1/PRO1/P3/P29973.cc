#include <iostream>
using namespace std;

// numero > 0
// n linies de piramide a la dreta

int main () {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i){
        for (int y = 0; y <= i; ++y){
            cout << '*';
        }
        cout << endl;
    }
}