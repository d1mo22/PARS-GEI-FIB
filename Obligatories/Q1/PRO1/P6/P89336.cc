#include <iostream>
using namespace std;

void inverse(int& count) {
    string s;
    if (cin >> s) {
        ++count;
        inverse(count);
        if (count <= 0) cout << s << endl;
        count -= 2;
    }
}

int main() {
    int count = 0;
    inverse(count);
}