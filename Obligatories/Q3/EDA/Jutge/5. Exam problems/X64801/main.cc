#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

bool es_ciclic(const VVI &graf, int n, VI &ge) {
  queue<int> q;
  for (int i = 0; i < n; ++i) {
    if (ge[i] == 0)
      q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    --n;
    for (int v : graf[u]) {
      --ge[v];
      if (ge[v] == 0)
        q.push(v);
    }
  }
  return n > 0;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    VVI g(n);
    VI ge(n);
    for (int i = 0; i < m; ++i) {
      int x, y;
      cin >> x >> y;
      g[x].push_back(y);
      ++ge[y];
    }
    cout << (es_ciclic(g, n, ge) ? "yes" : "no") << endl;
  }
}
