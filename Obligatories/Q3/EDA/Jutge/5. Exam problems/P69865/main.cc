#include <iostream>
#include <stack>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PI;

const PI knight[8] = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},
                      {1, 2},   {2, 1},   {2, -1}, {1, -2}};

const PI bisharp[4] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

int n, m;
int tresors = 0;

bool pos_ok(int i, int j, const VVC &tauler) {
  return ((i >= 0) and (i < n) and (j >= 0) and (j < m) and
          (tauler[i][j] != 'T'));
}

int dfs_k(const PI &start, VVI &visitats, VVC &tauler) {
  stack<PI> q;
  int suma = 0;

  q.push(start);

  while (!q.empty() and (tresors != 0)) {
    PI e = q.top();
    int x = e.first;
    int y = e.second;
    q.pop();
    char cela = tauler[x][y];

    if (!visitats[x][y]) {
      visitats[x][y] = true;

      if ((cela >= '0') and (cela <= '9')) {
        suma += cela - '0';
        tauler[x][y] = 'T';
      }

      for (int i = 0; i < 8; ++i) {
        int xx = x + knight[i].first;
        int yy = y + knight[i].second;
        if (pos_ok(xx, yy, tauler) and !visitats[xx][yy]) {
          q.push({xx, yy});
        }
      }
    }
  }
  return suma;
}

int dfs_b(const PI &start, VVI &visitats, VVC &tauler) {
  stack<PI> q;
  int suma = 0;

  q.push(start);

  while (!q.empty() and (tresors != 0)) {
    PI e = q.top();
    int x = e.first;
    int y = e.second;
    q.pop();

    if (!visitats[x][y]) {
      visitats[x][y] = true;
      char cela = tauler[x][y];

      if ((cela >= '0') and (cela <= '9')) {
        suma += cela - '0';
        tauler[x][y] = 'T';
      }

      for (int i = 0; i < 4; ++i) {
        int xx = x + bisharp[i].first;
        int yy = y + bisharp[i].second;
        if (pos_ok(xx, yy, tauler) and !visitats[xx][yy]) {
          q.push({xx, yy});
        }
      }
    }
  }
  return suma;
}

int main() {
  while (cin >> n >> m) {
    vector<PI> caballs;
    vector<PI> alfils;
    VVC tauler(n, VC(m));
    int k = 0, b = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        char c;
        cin >> c;
        if (c == 'B') {
          alfils.push_back(make_pair(i, j));
          ++b;
        } else if (c == 'K') {
          caballs.push_back(make_pair(i, j));
          ++k;
        } else if ((c >= '0') and (c <= '9'))
          ++tresors;
        tauler[i][j] = c;
      }

    int punts = 0;
    for (int i = 0; i < k; ++i) {
      PI pos = caballs[i];
      VVI visitats(n, VI(m, false));
      punts += dfs_k(pos, visitats, tauler);
    }
    for (int i = 0; i < b; ++i) {
      PI pos = alfils[i];
      VVI visitats(n, VI(m, false));
      punts += dfs_b(pos, visitats, tauler);
    }
    cout << punts << endl;
  }
}
