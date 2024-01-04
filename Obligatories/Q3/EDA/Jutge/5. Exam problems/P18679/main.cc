#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;

void backtrack(const VI &salts, int m, int n, int idx, int sum) {
  if (n == idx)
    cout << sum << endl;
  else {
    if (sum + salts[idx] <= m / 2)
      backtrack(salts, m, n, idx + 1, sum + salts[idx]);
    if (sum - salts[idx] >= -m / 2) 
      backtrack(salts, m, n, idx + 1, sum - salts[idx]);
  }
}

int main() {
  int m, n;
  cin >> m >> n;
  VI salts(n);
  for (int i = 0; i < n; ++i)
    cin >> salts[i];
  backtrack(salts, m, n, 0, 0);
}
