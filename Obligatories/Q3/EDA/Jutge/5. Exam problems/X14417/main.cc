#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef vector<VS> VVS;
typedef pair<int, int> PI;

const PI dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool pos_ok(const VVS &tauler, int n, int m, int i, int j) {
  return ((i >= 0) and (i < n) and (j >= 0) and (j < m) and
          (tauler[i][j] != "*"));
}

int BFS(const VVS &tauler, PI &ini, int n, int m, PI &obj) {
  queue<PI> q;
  VVI distancia(n, VI(m, -1));

  distancia[ini.first][ini.second] = 0;
  q.push(ini);

  while (!q.empty()) {
    PI p = q.front();
    q.pop();

    int i = p.first;
    int j = p.second;
    if (p == obj) {
      return distancia[i][j];
    }

    for (PI e : dir) {
      int ii = i + e.first;
      int jj = j + e.second;
      if (pos_ok(tauler, n, m, ii, jj) and distancia[ii][jj] == -1) {
        distancia[ii][jj] = distancia[i][j] + 1;
        q.push(PI(ii, jj));
      }
    }
  }
  return -1;
}

PI position(const VVS &tauler, const string &s) {
  int n = tauler.size();
  int m = tauler[0].size();
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      if (tauler[i][j] == s)
        return PI(i, j);
    }
  return PI(-1, -1);
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    VVS tauler(n, VS(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cin >> tauler[i][j];
      }
    }
    int t;
    cin >> t;
    VS busca(t);
    for (int i = 0; i < t; ++i)
      cin >> busca[i];

    vector<PI> pos(t + 1);
    pos[0] = PI(0, 0);
    for (int i = 0; i < t; ++i) {
      pos[i + 1] = position(tauler, busca[i]);
    }

    int pasos = 0;
    bool ok = true;
    int x = pos.size() - 1;
    for (uint i = 0; ok and i < x; ++i) {
      int d = BFS(tauler, pos[i], n, m, pos[i + 1]);
      if (d == -1)
        ok = false;
      else
        pasos += d;
    }
    if (!ok)
      cout << "impossible" << endl;
    else
      cout << pasos + t << endl;
  }
}
