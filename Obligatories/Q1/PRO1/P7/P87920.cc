#include <iostream>
#include <vector>
using namespace std;

// Equal to the sum of the rest (II)

int suma(const vector<int>& v, int n) {
    int sum = 0;
    for (int j = 0; j < n; ++j) {
        sum += v[j];
    }
    return sum;
}
bool existeix(const vector<int>& v, int n) {
    int sum = suma(v, n);
    for (int i = 0; i < n; ++i) {
        if (2*v[i] == sum) return true;
    }
    return false;
}
int main() {
    int n;
    while (cin >> n) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        if (existeix(v, n)) cout << "YES";
        else cout << "NO";
        cout << endl;
    }
}