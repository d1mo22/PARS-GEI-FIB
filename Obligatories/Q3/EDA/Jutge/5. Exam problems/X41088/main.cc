#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;

bool valid(int idx, const VI &v, int n) {
  return (v[idx - 2] + n <= 2 * v[idx - 1]);
}

void escriu(const VI &sol) {
  int n = sol.size() - 1;
  cout << '(';
  for (int i = 0; i < n; ++i) {
    cout << sol[i] << ',';
  }
  cout << sol[n] << ')' << endl;
}

void pou(int n, VI &sol, VI &usat, int idx) {
  if (idx == n) {
    escriu(sol);
    return;
  } else {
    for (int i = 1; i <= n; ++i) {
      if (!usat[i] and (sol.size() < 2 or valid(idx, sol, i))) {
        usat[i] = true;
        sol.push_back(i);
        pou(n, sol, usat, idx + 1);
        sol.pop_back();
        usat[i] = false;
      }
    }
  }
}

int main() {
  int n;
  cin >> n;
  VI sol;
  VI usat(n + 1, false);
  pou(n, sol, usat, 0);
}
