#include <iostream>
using namespace std;

int avalua() {
    char c;
    cin >> c;

    if (c == '+') return avalua() + avalua();
    if (c == '-') return avalua() - avalua();
    if (c == '*') return avalua()*avalua();
    return c - '0';
}

int main() {
    cout << avalua() << endl;
}
