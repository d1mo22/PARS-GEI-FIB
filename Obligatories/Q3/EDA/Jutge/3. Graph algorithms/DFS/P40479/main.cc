#include <iostream>
#include <stack>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PI;

int n, m;
const PI moviments[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool pos_ok(int x, int y, const VVC &tauler) {
  return ((x >= 0) and (x < n) and (y >= 0) and (y < m) and
          (tauler[x][y] != '#'));
}

void omplir_tauler(VVC &tauler, const PI &start, const char &c) {
  stack<PI> q;
  VVI visitats(n, VI(m, false));
  q.push(start);

  while (!q.empty()) {
    PI e = q.top();
    int x = e.first;
    int y = e.second;
    q.pop();

    if (!visitats[x][y]) {
      visitats[x][y] = true;
      if (tauler[x][y] == '.')
        tauler[x][y] = c;

      for (int i = 0; i < 4; ++i) {
        int xx = x + moviments[i].first;
        int yy = y + moviments[i].second;
        if (pos_ok(xx, yy, tauler) and !visitats[xx][yy])
          q.push({xx, yy});
        ;
      }
    }
  }
}

void escriu(const VVC &tauler) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << tauler[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

void buscar_lletres(VVC &tauler, const vector<pair<int, int>> &lletres) {
  int n = lletres.size();
  for (int i = 0; i < n; ++i) {
    PI e = lletres[i];
    omplir_tauler(tauler, e, tauler[e.first][e.second]);
  }
}

int main() {
  while (cin >> n >> m) {
    VVC tauler(n, VC(m));
    vector<pair<int, int>> lletres;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        char c;
        cin >> c;
        if (((c >= 'A') and (c <= 'Z')) or ((c >= 'a') and (c <= 'z'))) {
          lletres.push_back({i, j});
        }
        tauler[i][j] = c;
      }
    buscar_lletres(tauler, lletres);
    escriu(tauler);
  }
}
