#include <iostream>
#include <vector>
using namespace std;

int binary_search(const vector<double> &v, int e, int d, double x) {
  if (e > d)
    return e;
  else {
    int m = e + (d - e) / 2;
    if (v[m] > x)
      return binary_search(v, e, m - 1, x);
    else // v[m] <= x
      return binary_search(v, m + 1, d, x);
    return m;
  }
}

int mes_a_la_dreta(double x, const vector<double> &v) {
  return binary_search(v, 0, v.size() - 1, x);
}

int main() {
  int n;
  while (cin >> n) {
    vector<double> V(n);
    for (int i = 0; i < n; ++i)
      cin >> V[i];
    int t;
    cin >> t;
    while (t--) {
      double x;
      cin >> x;
      cout << mes_a_la_dreta(x, V) << endl;
    }
  }
}
