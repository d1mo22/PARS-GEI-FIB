#include <iostream>
#include <vector>
using namespace std;

void escriu_solucions(vector<int> &rosers, vector<int> &sol_parcial,
                      bool consec, int idx) {
  if (idx == sol_parcial.size()) {
    if (consec) {
      for (int x : sol_parcial)
        cout << x;
      cout << endl;
    }
  } else {
    for (int r = 1; r <= 3; ++r) {
      if (rosers[r] > 0 and
          (not consec or idx == 0 or sol_parcial[idx - 1] != r)) {
        sol_parcial[idx] = r;
        --rosers[r];
        escriu_solucions(rosers, sol_parcial,
                         consec or (idx > 0 and sol_parcial[idx - 1] == r),
                         idx + 1);
        ++rosers[r];
      }
    }
  }
}
void escriu_solucions(int n) {
  vector<int> sol_parcial(3 * n);
  vector<int> rosers(4, n); // rosers[0] no utilitzat
  escriu_solucions(rosers, sol_parcial, false, 0);
}

int main() {
  int n;
  while (cin >> n) {
    escriu_solucions(n);
    cout << string(10, '*') << endl;
  }
}
