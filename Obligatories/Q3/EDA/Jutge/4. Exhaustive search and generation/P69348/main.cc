#include <iostream>
#include <vector>
using namespace std;

void escriu(const vector<int>& v) {
    int n = v.size();
    cout << '(';
    for(int i = 0; i < n-1; ++i) cout << v[i] << ',';
    cout << v[n-1] << ')' << endl;
}

void permutacions(vector<int>& v, vector<bool>& usat, int i) {
    if (i == v.size()) escriu(v);
    else {
        for(int j = 1; j < usat.size(); ++j) {
            if (!usat[j]) {
                v[i] = j;
                usat[j] = true;
                permutacions(v, usat, i+1);
                usat[j] = false;
            }
        }
    }
}

void permutacions(int n) {
    vector<int> v(n);
    vector<bool> u(n+1);
    permutacions(v,u,0);
}

int main() {
    int n;
    cin >> n;
    permutacions(n);
}