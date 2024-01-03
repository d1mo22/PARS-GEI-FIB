#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;
typedef pair<int, int> PI;
typedef vector<vector<int>> VVI;

const PI knight[8] = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},
                      {1, 2},   {2, 1},   {2, -1}, {1, -2}};

bool pos_ok(const VVC &tauler, int x, int y, int n, int m) {
  return ((x >= 0) and (x < n) and (y >= 0) and (y < m) and
          (tauler[x][y] != 'X'));
}

int buscar(const VVC &tauler, int x, int y, int n, int m) {
  queue<PI> q;
  VVI distancia(n, vector<int>(m, -1));
  distancia[x][y] = 0;
  q.push(PI(x, y));
  while (!q.empty()) {
    PI p = q.front();
    q.pop();
    int i = p.first;
    int j = p.second;
    if (tauler[i][j] == 'p')
      return distancia[i][j];
    for (int k = 0; k < 8; ++k) {
      int ii = i + knight[k].first;
      int jj = j + knight[k].second;
      if (pos_ok(tauler, ii, jj, n, m) and distancia[ii][jj] == -1) {
        q.push(PI(ii, jj));
        distancia[ii][jj] = distancia[i][j] + 1;
      }
    }
  }
  return -1;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    VVC tauler(n, VC(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cin >> tauler[i][j];
      }
    }
    int x, y;
    cin >> x >> y;
    int pasos = buscar(tauler, x - 1, y - 1, n, m);
    if (pasos == -1)
      cout << "no" << endl;
    else
      cout << pasos << endl;
  }
}
