#include <iostream>
#include <vector>
using namespace std;

int trobar_error(double x, const vector<double> &v, int e, int d) {
  if (e > d)
    return -1;
  else {
    int m = (d + e) / 2;
    if (v[m] == x) {
      int p_left = trobar_error(x, v, e, m - 1);
      if (p_left == -1)
        return m;
      else
        return p_left;
    } else if (v[m] > x) {
      int p_left = trobar_error(x, v, e, m - 1);
      if (p_left == -1) {
        if (m + 1 <= d and v[m + 1] == x)
          return m + 1;
        else
          return -1;
      } else
        return p_left;
    } else { // v[m] < x
      if (m - 1 >= e and v[m - 1] == x)
        return m - 1;
      return trobar_error(x, v, m + 1, d);
    }
  }
}

int first_occurrence(double x, const vector<double> &v) {
  return trobar_error(x, v, 0, v.size() - 1);
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
      cout << first_occurrence(x, V) << endl;
    }
  }
}
