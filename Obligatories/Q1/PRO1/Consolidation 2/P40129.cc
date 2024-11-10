#include <iostream>
#include <string>
using namespace std;

int validar(const string& s) {
    int pos = 0;
    int suma = 0;
    for (int i = 10; i != 0; --i) {
        if (s[pos] == 'X') suma += 10 * i;
        else if (s[pos] != '?') suma += (s[pos] - '0') * i;
        ++pos;
    }
    return suma;
}

int posicio_interrogant(const string& s) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '?') return 10 - i;
    }
    return -1;
}

char missing(int suma, int pos) {
    for (int i = 0; i <= 10; ++i) {
        if ((suma + (i * pos)) % 11 == 0) {
            return (i == 10) ? 'X' : (i + '0');
        }
    }
    return 'X'; // This should never be reached if the input is valid
}

int main() {
    string s;
    while (cin >> s) {
        int suma = validar(s);
        int pos = posicio_interrogant(s);
        char digit = missing(suma, pos);
        cout << digit << endl;
    }
    return 0;
}
