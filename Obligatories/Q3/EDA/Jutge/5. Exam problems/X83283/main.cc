#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

int BFS(const VVI &g) {
  int n = g.size();
  VI distancia(n, -1);
  distancia[0] = 0;
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : g[u]) {
      if (distancia[v] == -1) {
        distancia[v] = distancia[u] + 1;
        q.push(v);
      }
    }
  }
  int res = 0;
  for (int v = 1; v < n; ++v) {
    if (distancia[v] != -1 and distancia[v] > distancia[res])
      res = v;
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
    cout << BFS(g) << endl;
  }
}
