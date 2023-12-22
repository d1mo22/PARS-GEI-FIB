#include <iostream>
#include <vector>
using namespace std;

void escriu(const vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n-1; ++i) cout << v[i] << " ";
    cout << v[n-1] << endl;
}

void binari(vector<int>& v, int i, int zero, int uns, int u) {
    if (i == v.size()) escriu(v);
    else {
        if (zero < v.size() - u) {
            v[i] = 0;binari(v, i+1, zero+1, uns, u);
        }   
        if (uns < u){
            v[i] = 1;binari(v, i+1,zero, uns+1, u);
        }
    }
}

void binari(int n, int u) {
    vector<int> v(n);
    binari(v, 0, 0, 0, u);
}

int main() {
    int n, u;
    cin >> n >> u;
    binari(n, u);
}