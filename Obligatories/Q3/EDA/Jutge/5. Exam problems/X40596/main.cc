#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;

void escriu(const VI &sol) {
  cout << '(';
  int n = sol.size() - 1;
  for (int i = 0; i < n; ++i) {
    cout << sol[i] << ',';
  }
  cout << sol[n] << ')' << endl;
}

void equilibrades(int n, int idx, int d, VI &sol, VI &usat, int ant) {
  if (idx == n) {
    escriu(sol);
    return;
  } else {
    for (int i = 1; i <= n; ++i) {
      if (!usat[i] and (abs(ant - i) <= d or sol.size() == 0)) {
        usat[i] = true;
        sol.push_back(i);
        equilibrades(n, idx + 1, d, sol, usat, i);
        sol.pop_back();
        usat[i] = false;
      }
    }
  }
}

int main() {
  int n, d;
  cin >> n >> d;
  VI sol;
  VI usat(n + 1);
  equilibrades(n, 0, d, sol, usat, 0);
}
