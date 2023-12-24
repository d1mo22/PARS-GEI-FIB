#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> PI;
typedef vector<PI> VP;
typedef vector<VP> VVP;
typedef vector<int> VI;

int n, m;

void dijkstra(const VVP &graph, int x, int y, VI &d, VI &camins) {
  d[x] = 0;
  camins[x] = 1;
  priority_queue<PI> q;
  q.push(PI(0, x));

  while (!q.empty()) {
    int p = -q.top().first;
    int v = q.top().second;
    q.pop();

    if (p == d[v]) {
      if (v == y)
        return;

      int x = graph[v].size();
      for (int i = 0; i < x; ++i) {
        int adj = graph[v][i].first;
        int pes = graph[v][i].second;
        if (p + pes < d[adj]) {
          camins[adj] = camins[v];
          d[adj] = p + pes;
          q.push(PI(-d[adj], adj));
        } else if (p + pes == d[adj])
          camins[adj] += camins[v];
      }
    }
  }
}

int main() {
  while (cin >> n >> m) {
    VVP graph(n);
    for (int i = 0; i < m; ++i) {
      int u, v, c;
      cin >> u >> v >> c;
      graph[u].push_back({v, c});
    }
    int x, y;
    cin >> x >> y;
    VI D(n, INT_MAX);
    VI camins(n, 0);
    dijkstra(graph, x, y, D, camins);

    if (D[y] != INT_MAX)
      cout << "cost " << D[y] << ", " << camins[y] << " way(s)" << endl;
    else
      cout << "no path from " << x << " to " << y << endl;
  }
}
