#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

void dfs(int u, const VVI &g, VI &vis) {
  if (vis[u])
    return;
  vis[u] = true;
  for (int v : g[u]) {
    dfs(v, g, vis);
  }
}

int main() {
  int n, u, v, m;
  while (cin >> n >> u >> v >> m) {
    VVI g(n);
    VVI i(n);
    for (int j = 0; j < m; ++j) {
      int x, y;
      cin >> x >> y;
      g[x].push_back(y);
      i[y].push_back(x);
    }
    VI fwd(n, false);
    dfs(u, g, fwd);
    if (!fwd[u])
      cout << 0 << endl;
    else {
      VI bwd(n, false);
      dfs(v, i, bwd);
      int sum = 0;
      for (int x = 0; x < n; ++x) {
        sum += (fwd[x] and bwd[x]);
      }
      if (sum != 0)
        cout << sum - 2 << endl;
      else
        cout << sum << endl;
    }
  }
}
