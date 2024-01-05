#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<string> VS;
typedef vector<VS> VVS;

void escriu(const VVS &conjunts, int x) {
  for (int i = 0; i < x; ++i) {
    cout << "subconjunt " << i + 1 << ": {";
    int n = conjunts[i].size();
    for (int j = 0; j < n; ++j) {
      cout << conjunts[i][j];
      if (j < n - 1)
        cout << ",";
    }
    cout << "}" << endl;
  }
  cout << endl;
}

void combinacions(const VS &paraules, VVS &conjunts, int n, int x, int idx) {
  if (idx == n)
    escriu(conjunts, x);
  else {
    for (int i = 0; i < x; ++i) {
      conjunts[i].push_back(paraules[idx]);
      combinacions(paraules, conjunts, n, x, idx + 1);
      conjunts[i].pop_back();
    }
  }
}

int main() {
  int n;
  cin >> n;
  VS paraules(n);
  for (int i = 0; i < n; ++i)
    cin >> paraules[i];
  int x;
  cin >> x;
  VVS conjunts(x);
  combinacions(paraules, conjunts, n, x, 0);
}
