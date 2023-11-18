#include <iostream>
#include <vector>
using namespace std;

bool search_aux(double x, const vector<double>& v, int left, int right) {
    if (left > right) return false;

    if (left + 1 >= right) return v[left] == x or v[right] == x;

    int half = (left + right)/2;

    if (v[half] > x) return v[half + 1] == x or search_aux(x, v, left, half - 1);
    if (v[half] < x) return v[half - 1] == x or search_aux(x, v, half + 1, right);
    return true;
}

bool resistant_search(double x, const vector<double>& v) {
    return search_aux(x, v, 0, v.size() - 1);
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
            cout << resistant_search(x, V) << endl;
        }
    }
}
