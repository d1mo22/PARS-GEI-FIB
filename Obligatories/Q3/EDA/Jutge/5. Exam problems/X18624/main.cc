#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> VC;

bool es_vocal(const char &c) {
  return ((c == 'a') or (c == 'e') or (c == 'i') or (c == 'o') or (c == 'u'));
}

void runes(const VC &lletres, VC &sol, int n, int idx) {
  if (idx == n) {
    for (char c : sol)
      cout << c;
    cout << endl;
    return;
  }
  for (char c : lletres) {
    if (!es_vocal(c) or idx == 0 or !es_vocal(sol[idx - 1])) {
      sol[idx] = c;
      runes(lletres, sol, n, idx + 1);
    }
  }
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    VC lletres(m);
    for (int i = 0; i < m; ++i) {
      cin >> lletres[i];
    }
    sort(lletres.begin(), lletres.end());
    VC sol(n);
    runes(lletres, sol, n, 0);
    cout << "----------" << endl;
  }
}
