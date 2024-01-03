#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PI;

VI BFS(const VVI &graf, int origen, int n) {
  VI pare(n, -1);
  pare[origen] = -1;
  queue<int> q;
  q.push(origen);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    VI vei = graf[u];
    sort(vei.begin(), vei.end());

    for (int v : vei) {
      if (pare[v] == -1) {
        pare[v] = u;
        q.push(v);
      }
    }
  }
  return pare;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    VVI graf(n);
    for (int i = 0; i < m; ++i) {
      int origen, destino;
      cin >> origen >> destino;
      graf[origen].push_back(destino);
    }
    VI distancia = BFS(graf, 0, n);
    VI cami;
    int node = n - 1;
    while (node != 0) {
      cami.push_back(node);
      node = distancia[node];
    }
    cami.push_back(0);
    reverse(cami.begin(), cami.end());
    int l = cami.size();
    for (int i = 0; i < l - 1; ++i)
      cout << cami[i] << " ";
    cout << cami[l - 1] << endl;
  }
}
