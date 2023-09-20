#include <iostream>
using namespace std;

void inverse() {
    string s;
    if (cin >> s and s != "end") {
        inverse();
        cout << s << endl;
    }
}

int main() {
    inverse();
} 