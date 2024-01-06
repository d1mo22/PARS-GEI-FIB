#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PI;

const PI mov[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool pos_ok(const VVC &tauler, int n, int m, int i, int j) {
  return ((i >= 0) and (i < n) and (j >= 0) and (j < m) and
          (tauler[i][j] != '#'));
}

int BFS(const VVC &tauler, int n, int m) {
  VVI visitat(n, VI(m, false));
  VVI distancia(n, VI(m, -1));
  queue<PI> q;

  distancia[0][0] = 0;
  q.push(PI(0, 0));

  while (!q.empty()) {
    PI p = q.front();
    q.pop();

    int i = p.first;
    int j = p.second;
    if (tauler[i][j] == 'T')
      return distancia[i][j];
    if (!visitat[i][j]) {
      visitat[i][j] = true;
      for (PI v : mov) {
        int ii = i + v.first;
        int jj = j + v.second;
        if (pos_ok(tauler, n, m, ii, jj) and !visitat[ii][jj]) {
          distancia[ii][jj] = distancia[i][j] + 1;
          q.push(PI(ii, jj));
        }
      }
    }
  }
  return -1;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    VVC tauler(n, VC(m));
    bool teleco = false;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        char c;
        cin >> c;
        if (c == 'T')
          teleco = true;
        tauler[i][j] = c;
      }
    }
    if (!teleco)
      cout << "El telecos ha figut." << endl;
    else {
      int dist = BFS(tauler, n, m);
      if (dist == -1)
        cout << "El telecos esta amagat." << endl;
      else {
        cout << dist << endl;
      }
    }
  }
}
