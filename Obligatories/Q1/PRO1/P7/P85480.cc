#include <iostream>
#include <vector>
using namespace std;

//Parells d'una seqüència (1)

bool prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i*i <= n; ++i) {
        if (n%i == 0) return false;
    }
  return true;
}

void parell(const vector<int>& v, int n) {
    int i = 0;
    bool trobat = false;
    while (i < n - 1 and not trobat) {
        int j = i + 1;

        while (j < n and not trobat) {
            if (i != j) trobat = prime(v[i]+v[j]);
            ++j;
        }
        ++i;
    } 
        if (trobat) cout << "si" << endl;
        else cout << "no" << endl;
}

int main() {
    int n;
    while(cin >> n) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        parell(v, n);   
    }
    
}