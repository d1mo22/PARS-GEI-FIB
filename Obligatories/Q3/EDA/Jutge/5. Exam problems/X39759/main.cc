#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PI;

const int infinite = numeric_limits<int>::max();

const PI mov[8] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                   {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

bool pos_ok(int i, int j, int n, int m) {
  return ((i >= 0) and (i < n) and (j >= 0) and (j < m));
}

int bfs(int n, int m, const PI &ini, const PI &obj) {
  VVI distancia(n, VI(m, infinite));
  queue<PI> q;

  distancia[ini.first][ini.second] = 0;
  q.push(ini);

  while (!q.empty()) {
    PI x = q.front();
    q.pop();

    if (x == obj)
      return distancia[x.first][x.second];

    for (auto &d : mov) {
      PI y = x;
      y.first += d.first;
      y.second += d.second;
      if (pos_ok(y.first, y.second, n, m) and
          distancia[y.first][y.second] == infinite) {
        distancia[y.first][y.second] = distancia[x.first][x.second] + 1;
        q.push(y);
      }
    }
  }
  return -1;
}

int main() {
  int n, m, W, L, p;
  while (cin >> n >> m >> W >> L >> p) {
    vector<PI> obj(p + 1);
    obj[0] = PI(0, 0);
    for (int i = 1; i <= p; ++i) {
      int f, c;
      cin >> f >> c;
      obj[i] = PI(f, c);
    }

    int punts = 0;
    int millor_puntuacio = 0;
    bool parar = false;
    int x = obj.size() - 1;

    for (int i = 0; !parar and i < x; ++i) {
      int d = bfs(n, m, obj[i], obj[i + 1]);
      if (d == -1)
        parar = true;
      else {
        punts += W;
        punts -= L * d;
        if (punts > millor_puntuacio)
          millor_puntuacio = punts;
      }
    }
    cout << millor_puntuacio << endl;
  }
}
