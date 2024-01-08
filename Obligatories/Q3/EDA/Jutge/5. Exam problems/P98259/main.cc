#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<char> VC;
typedef vector<VC> VVC;
typedef vector<VI> VVI;
typedef pair<int, int> PI;

const PI DIR[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool pos_ok(const VVC &tauler, int i, int j) {
  return ((i >= 0) and (i < tauler.size()) and (j >= 0) and
          (j < tauler[0].size()) and tauler[i][j] != '#');
}

PI cerca(const VVC &tauler) {
  int n = tauler.size(), m = tauler[0].size();
  VVI dist(n, VI(m, INT_MAX)), pers(n, VI(m, -1));
  queue<PI> q;
  q.push(PI(0, 0));
  dist[0][0] = 0;
  pers[0][0] = (tauler[0][0] == 'P');

  while (!q.empty()) {
    int i = q.front().first;
    int j = q.front().second;
    q.pop();

    if (tauler[i][j] == 'T')
      return PI(dist[i][j], pers[i][j]);
    for (auto &d : DIR) {
      int ii = i + d.first;
      int jj = j + d.second;
      int nd = dist[i][j] + 1;
      if (pos_ok(tauler, ii, jj)) {
        int np = pers[i][j] + int(tauler[ii][jj] == 'P');
        if (dist[ii][jj] == INT_MAX) {
          q.push(PI(ii, jj));
          dist[ii][jj] = nd;
          pers[ii][jj] = np;
        } else if (dist[ii][jj] == nd and pers[ii][jj] < np)
          pers[ii][jj] = np;
      }
    }
  }
  return PI(-1, 0);
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    VVC tauler(n, VC(m));
    bool trobat = false;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cin >> tauler[i][j];
        if (tauler[i][j] == 'T')
          trobat = true;
      }
    }
    if (!trobat)
      cout << "El telecos ha fugit." << endl;
    else {
      PI res = cerca(tauler);
      if (res.first == -1)
        cout << "El telecos esta amagat." << endl;
      else
        cout << res.first << " " << res.second << endl;
    }
  }
}
