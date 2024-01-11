#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> PI;
typedef vector<PI> VP;
typedef vector<VP> VVP;
typedef vector<int> VI;

int dijkstra(const VVP &graf, int x, int y) {
  int n = graf.size();
  priority_queue<PI, VP, greater<PI>> q;
  VI distancia(n, INT_MAX);

  distancia[x] = 0;
  q.push(PI(0, x));
  while (!q.empty()) {
    PI p = q.top();
    q.pop();
    int u = p.second;
    int d = p.first;
    if (u == y)
      return distancia[y];
    if (d == distancia[u]) {
      for (PI t : graf[u]) {
        int v = t.second;
        int l = t.first;
        int d2 = max(distancia[u], l);
        if (d2 < distancia[v]) {
          distancia[v] = d2;
          q.push(PI(d2, v));
        }
      }
    }
  }
  return -1;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    VVP graf(n);
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      graf[u].push_back({w, v});
    }
    cout << dijkstra(graf, 0, 1) << endl;
  }
}
