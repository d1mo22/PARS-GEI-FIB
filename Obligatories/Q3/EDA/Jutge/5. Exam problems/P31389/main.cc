#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;
typedef vector<int> VI;

void escriu(const VI &torres, int n, int m) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (torres[i] == j)
        cout << 'R';
      else
        cout << '.';
    }
    cout << endl;
  }
  cout << endl;
}

void combinacions(VI &torres, int n, int m, int idx, VI &usat) {
  if (idx == n) {
    escriu(torres, n, m);
    return;
  }
  for (int i = 0; i < m; ++i) {
    if (!usat[i]) {
      usat[i] = true;
      torres[idx] = i;
      combinacions(torres, n, m, idx + 1, usat);
      usat[i] = false;
      torres[idx] = -1;
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  VI torres(n, -1);
  VI usat(m, false);
  combinacions(torres, n, m, 0, usat);
}
