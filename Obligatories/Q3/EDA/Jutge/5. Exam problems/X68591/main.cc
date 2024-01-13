#include <iostream>
#include <limits>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PI;

int infinite = numeric_limits<int>::max();

int size_component(const VVI &g, VI &visitat, int u) {
  visitat[u] = true;
  int total = 1;
  for (int v : g[u]) {
    if (!visitat[v])
      total += size_component(g, visitat, v);
  }
  return total;
}

PI components(const VVI &g) {
  int n = g.size();
  PI res = PI(infinite, 0);
  VI visitat(n, false);
  for (int i = 0; i < n; ++i) {
    if (!visitat[i]) {
      int s = size_component(g, visitat, i);
      res.first = min(res.first, s);
      res.second = max(res.second, s);
    }
  }
  return res;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    VVI g(n);
    for (int i = 0; i < m; ++i) {
      int x, y;
      cin >> x >> y;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    PI p = components(g);
    cout << p.first << ' ' << p.second << endl;
  }
}
