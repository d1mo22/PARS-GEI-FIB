#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;
typedef pair<int, int> PI;

const PI mov[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool pos_ok(const VVC &tauler, int i, int j, int n, int m) {
  return ((i >= 0) and (i < n) and (j >= 0) and (j < m) and
          (tauler[i][j] != 'X'));
}

PI BFS(const VVC &tauler, int x, int y, int n, int m) {
  queue<PI> q;
  vector<vector<int>> visitat(n, vector<int>(m, false));
  vector<vector<int>> distancia(n, vector<int>(m, -1));

  q.push(PI(x, y));
  // A dist.first tenim la distancia més llunyana
  // mentre que a dist.second tenim la segona distancia més llunyana
  PI dist = {-1, -1};
  distancia[x][y] = 0;

  while (!q.empty()) {
    PI pos = q.front();
    q.pop();
    int i = pos.first;
    int j = pos.second;

    if (!visitat[i][j]) {
      visitat[i][j] = true;
      int d = distancia[i][j];

      if (tauler[i][j] == 't') {
        if (d > dist.first) {
          dist.second = dist.first;
          dist.first = d;
        } else if (dist.second < d)
          dist.second = d;
      }

      for (int k = 0; k < 4; ++k) {
        int ii = i + mov[k].first;
        int jj = j + mov[k].second;
        if (pos_ok(tauler, ii, jj, n, m) and !visitat[ii][jj]) {
          distancia[ii][jj] = distancia[i][j] + 1;
          q.push(PI(ii, jj));
        }
      }
    }
  }
  return dist;
}

int main() {
  int n, m;
  cin >> n >> m;
  VVC tauler(n, VC(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> tauler[i][j];
  int x, y;
  cin >> x >> y;
  PI distancia = BFS(tauler, x - 1, y - 1, n, m);
  if (distancia.second == -1)
    cout << "no es pot arribar a dos o mes tresors" << endl;
  else
    cout << "segona distancia maxima: " << distancia.second << endl;
}
