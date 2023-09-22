#include <iostream>
#include <string>
using namespace std;

int validar(const string& s) {
    int pos = 0;
    int suma = 0;
    for (int i = 10; i != 0; --i) {
        if (s[pos] == 'X') suma += (s[pos] - 'N')*i ;
        else if (s[pos] != '?') suma += (s[pos] - '0')*i;
        ++pos;
    }
    return suma;
}

int posicio_interrogant(const string& s) {
    int pos = 0;
    for (int i = s.size() - 1; i != 0; --i) {
        if (s[i] == '?') return pos + 1;
        ++pos;
    }
    return -1;
}

char missing(int suma, int pos) {
    int i = 0;
    while (i < 10) {
        if ((suma+(i*pos))%11 == 0) return (i + '0');
        ++i;
    }
    return 'X';
}

int main() {
    string s;
    while (cin >> s) {
        int pos = posicio_interrogant(s);
        int suma = validar(s);
        cout << suma << " " << missing(suma, pos) << endl;
    }
}
