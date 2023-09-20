#include <vector>
#include <iostream>
using namespace std;

const int LONG_ALFABET = 'z' - 'a' + 1;

double llargada_mitja(const vector<string>& v, int n) {
    double l = 0;
    for (int i = 0; i < n; ++i) l += v[i].length();
    return l/n;
}

char lletra_mes_frequent(const string& s) {
    vector<int> lm(LONG_ALFABET, 0);
    int x = s.size();
    for (int i = 0; i < x; ++i) {
        ++lm[s[i]-'a'];
    }
    int pos = 0;
    int f = 0;

    for (int i = 0; i < LONG_ALFABET; ++i) {
        if (lm[i] > f) {
            pos = i;
            f = lm[i];
        }
    }
    char c = 'a' + pos;
    return c;
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(2);

    int n;
    cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    cout << llargada_mitja(v, n) << endl;

    for (int i = 0; i < n; ++i) {
        if (v[i].length() >= llargada_mitja(v,n)) {
            cout << v[i] << ": " << lletra_mes_frequent(v[i]) << endl;
        }
    }
    
}