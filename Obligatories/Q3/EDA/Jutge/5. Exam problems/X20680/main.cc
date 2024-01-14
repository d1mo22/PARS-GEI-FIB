#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> VC;

const char lletres[3] = {'x', 'y', 'z'};

void combinacions(VC &sol, int n, int c, int idx, int contador) {
  if (idx == n) {
    for (char c : sol)
      cout << c;
    cout << endl;
    return;
  }
  for (int k = 0; k < 3; ++k) {
    if (sol.size() == 0 or (sol[idx - 1] == lletres[k] and contador < c)) {
      sol[idx] = lletres[k];
      combinacions(sol, n, c, idx + 1, contador + 1);
    } else if (sol[idx - 1] != lletres[k]) {
      sol[idx] = lletres[k];
      combinacions(sol, n, c, idx + 1, 1);
    }
  }
}

int main() {
  int n, c;
  while (cin >> n >> c) {
    VC sol(n);
    combinacions(sol, n, c, 0, 0);
    cout << string(20, '-') << endl;
  }
}
