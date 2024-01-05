#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

void BFS(const VVI &graf, VI &distancia, int n) {
  queue<int> q;
  VI visitat(n, false);
  q.push(0);
  distancia[0] = 0;

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    if (!visitat[v]) {
      visitat[v] = true;

      for (int g : graf[v]) {
        if (!visitat[g]) {
          distancia[g] = distancia[v] + 1;
          q.push(g);
        }
      }
    }
  }
}

int main() {
  int n, t;
  while (cin >> n >> t) {
    VVI graf(n);
    for (int i = 0; i < t; ++i) {
      int x, v;
      cin >> x >> v;
      --x;
      for (int j = 0; j < x; ++j) {
        int m;
        cin >> m;
        graf[m].push_back(v);
        graf[v].push_back(m);
      }
    }
    VI distancia(n, INT_MAX);
    BFS(graf, distancia, n);
    for (int i = 0; i < n; ++i) {
      cout << i << " : ";
      if (distancia[i] == INT_MAX)
        cout << "no" << endl;
      else
        cout << distancia[i] << endl;
    }
    cout << "----------" << endl;
  }
}
