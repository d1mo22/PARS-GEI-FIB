#include <iostream>
#include <string>
#include <vector>
using namespace std;

void escriu(const vector<string>& p) {
    int n = p.size();
    cout << '(';
    for (int i = 0; i < n-1; ++i) cout << p[i] << ',';
    cout << p[n-1] << ')' << endl;
}

void permutacions(int n, const vector<string>& paraules, vector<string>& perm, vector<bool>& usat, int idx) {
    if (idx == n) escriu(perm);
    else {
        for (int k = 0; k < n; ++k) {
            if(!usat[k]) {
                perm[idx] = paraules[k];
                usat[k] = true;
                permutacions(n, paraules, perm, usat, idx+1);
                usat[k] = false;
            }
        }
    }
}

void permutacions(int n, const vector<string>& p) {
    vector<bool> p_usat(n);
    vector<string> perm(n);
    permutacions(n, p,perm,p_usat,0);
}

int main() {
    int n; cin >> n;
    vector<string> paraules(n);
    for(int i = 0; i < n; ++i) cin >> paraules[i];
    permutacions(n, paraules);
}