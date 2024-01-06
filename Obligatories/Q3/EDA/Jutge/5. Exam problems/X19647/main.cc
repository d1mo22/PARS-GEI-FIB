#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> PI;
typedef vector<int> VI;
typedef vector<vector<PI>> VVP;

int dijkstra(int x, int y, const VVP &graf, VI &distancia, const VI &vertex) {
  int n = graf.size();
  priority_queue<PI, vector<PI>, greater<PI>> q;
  VI visitat(n, false);
  distancia[x] = 0;
  q.push(PI(distancia[x], x));

  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    if (u == y)
      return distancia[u];
    if (!visitat[u]) {
      visitat[u] = true;
      for (PI p : graf[u]) {
        int v = p.second;
        int dv = p.first;
        int cost_v = distancia[u] + dv;
        if (v != y)
          cost_v += vertex[v];
        if (distancia[v] > cost_v) {
          distancia[v] = cost_v;
          q.push(PI(cost_v, v));
        }
      }
    }
  }
  return INT_MAX;
}

int main() {
  int n, m;
  cin >> n >> m;
  VVP graf(n);
  VI vertex(n);
  for (int i = 0; i < n; ++i)
    cin >> vertex[i];

  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    graf[u].push_back(PI(w, v));
    graf[v].push_back(PI(w, u));
  }
  int x, y;
  while (cin >> x >> y) {
    VI distancia(n, INT_MAX);
    int dist = dijkstra(x, y, graf, distancia, vertex);
    if (dist == INT_MAX)
      cout << "c(" << x << ',' << y << ") = +oo" << endl;
    else
      cout << "c(" << x << ',' << y << ") = " << dist << endl;
  }
}
