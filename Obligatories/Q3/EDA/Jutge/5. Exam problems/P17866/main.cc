#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PI;

const PI dir[8] = {{2, 1}, {-2, 1}, {2, -1}, {-2, -1},
                   {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};

bool pos_ok(int i, int j, const VVC &tauler) {
  int n = tauler.size();
  int m = tauler[0].size();
  return ((i >= 0) and (i < n) and (j >= 0) and (j < m) and
          (tauler[i][j] != 'X'));
}

int pastanagues(const VVC &tauler, int x, int y) {
  int n = tauler.size();
  int m = tauler[0].size();
  VVI distancia(n, VI(m, INT_MAX));
  queue<PI> q;

  distancia[x][y] = 0;
  q.push(PI(x, y));

  while (!q.empty()) {
    PI p = q.front();
    q.pop();
    if (tauler[p.first][p.second] == 'p')
      return distancia[p.first][p.second];
    for (int k = 0; k < 8; ++k) {
      int i = p.first + dir[k].first;
      int j = p.second + dir[k].second;
      if (pos_ok(i, j, tauler) and distancia[i][j] == INT_MAX) {
        distancia[i][j] = distancia[p.first][p.second] + 1;
        q.push(PI(i, j));
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
    int pasos = pastanagues(tauler, x - 1, y - 1);
    if (pasos == -1)
      cout << "no" << endl;
    else
      cout << pasos << endl;
  }
}
