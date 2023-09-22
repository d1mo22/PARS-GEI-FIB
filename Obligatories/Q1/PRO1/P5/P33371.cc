#include <iostream>
using namespace std;

char encoded(char c, int k) {
    if (c - 'a' >= 0 and c - 'a' <= 25) {
        k %= 26;
        int aux = ((int)c - (int)'a' + k)%26;
        c = 'A' + aux;
    }
    return c;
}

int main() {
    int k;
    char c;

    while (cin >> k ) {
        while (cin >> c and c != '.') {
            if (c == '_') cout << " ";
            else cout << encoded(c, k);
        }
        cout << endl;
    } 
}