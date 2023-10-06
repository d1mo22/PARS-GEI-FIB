#include <iostream>
#include <vector>
using namespace std;


int bin_search(const vector<double>& v, double x, int left, int right) {
    if (left > right) return -1;
    if (left == right) return (v[left] == x) ? left : -1;
    int half = (left + right)/2;
    if (v[half] < x) return bin_search(v, x, half + 1, right);
    else return bin_search(v, x, left, half); 
}

int first_occurrence(double x, const vector<double>& v) {
    int size = v.size() - 1;
    return bin_search(v, x, 0, size);
}

int main() {
    int n;
    while (cin >> n) {
        vector<double> V(n);
        for (int i = 0; i < n; ++i) cin >> V[i];
        int t;
        cin >> t;
        while (t--) {
            double x;
            cin >> x;
            cout << first_occurrence(x, V) << endl;
        }
    }
}
