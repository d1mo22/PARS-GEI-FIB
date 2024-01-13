#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PI;
typedef pair<int, PI> PPI;

const PI dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool objectiu(int n, int i, int j) {
  return ((i == 0) or (j == 0) or (i == n - 1) or (j == n - 1));
}

int dijkstra(const VVI &tauler, int n) {
  int x, y;
  x = y = n / 2;
  priority_queue<PPI, vector<PPI>, greater<PPI>> q;
  VVI distancia(n, VI(n, INT_MAX));
  distancia[x][y] = tauler[x][y];
  q.push({tauler[x][y], PI(x, y)});
  while (!q.empty()) {
    PPI p = q.top();
    q.pop();

    int i = p.second.first;
    int j = p.second.second;
    if (objectiu(n, i, j))
      return distancia[i][j];
    for (int k = 0; k < 4; ++k) {
      int ii = i + dir[k].first;
      int jj = j + dir[k].second;
      if (distancia[i][j] + tauler[ii][jj] < distancia[ii][jj]) {
        distancia[ii][jj] = distancia[i][j] + tauler[ii][jj];
        q.push(PPI(distancia[ii][jj], PI(ii, jj)));
      }
    }
  }
  return -1;
}

int main() {
  int n;
  while (cin >> n) {
    VVI tauler(n, VI(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cin >> tauler[i][j];
      }
    }
    cout << dijkstra(tauler, n) << endl;
  }
}
