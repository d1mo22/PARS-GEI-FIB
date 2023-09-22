#include <iostream>
using namespace std;

void inverse() {
    string s;
    if (cin >> s) {
        inverse();
        cout << s << endl;
    }
}

int main() {
    inverse();
}