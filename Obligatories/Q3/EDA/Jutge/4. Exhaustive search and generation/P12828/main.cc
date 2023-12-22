#include <iostream>
#include <vector>
using namespace std;

void escriu(const vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n - 1; ++i) cout << v[i] << " ";
    cout << v[n-1] << endl;
}

void zeros_i_uns(int n, int i, vector<int>& v) {
    if (i == n) escriu(v); 
    else {
        v[i] = 0;
        zeros_i_uns(n, i+1, v);
        v[i] = 1;
        zeros_i_uns(n, i+1, v);
    }
}

int main() {
    int x; cin >> x;
    vector<int> v(x);
    zeros_i_uns(x, 0, v);
}