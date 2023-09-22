#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int spaces = n - 1;
    int cross = 1;

    //Part inicial del rombe
    for (int i = spaces; i > 0; --i) {
        for (int j = 0; j < spaces; ++j) cout << " ";
        for (int j = 0; j < cross; ++j) cout << "*";
        cout << endl;
        cross += 2;
        spaces -= 1;
    }

    //Part final del rombe
    for (int i = spaces; i < n; ++i) {
        for (int j = 0; j < spaces; ++j) cout << " ";
        for (int j = 0; j < cross; ++j) cout << "*"; 
        cout << endl;
        cross -= 2;
        spaces += 1;
    }
}