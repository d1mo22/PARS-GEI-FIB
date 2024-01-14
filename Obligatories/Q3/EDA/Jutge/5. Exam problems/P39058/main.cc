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

bool pos_ok(const VVC &tauler, int i, int j, int n, int m) {
  return ((i >= 0) and (i < n) and (j >= 0) and (j < m) and
          (tauler[i][j] != 'a'));
}

pair<int, double> flors(const VVC &tauler, int x, int y) {
  int n = tauler.size();
  int m = tauler[0].size();
  VVI distancia(n, VI(m, INT_MAX));
  queue<PI> q;

  int contador = 0;
  double dist = 0;
  distancia[x][y] = 0;
  q.push(PI(x, y));

  while (!q.empty()) {
    PI p = q.front();
    q.pop();

    int i = p.first;
    int j = p.second;
    if (tauler[i][j] == 'F') {
      ++contador;
      dist += distancia[i][j];
    }
    for (int k = 0; k < 8; ++k) {
      int ii = i + dir[k].first;
      int jj = j + dir[k].second;
      if (pos_ok(tauler, ii, jj, n, m) and distancia[ii][jj] == INT_MAX) {
        distancia[ii][jj] = distancia[i][j] + 1;
        q.push(PI(ii, jj));
      }
    }
  }
  return {contador, dist / contador};
}

int main() {
  cout.setf(ios::fixed);
  cout.precision(4);

  int n, m;
  cin >> n >> m;
  PI caball;
  VVC tauler(n, VC(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> tauler[i][j];
      if (tauler[i][j] == 'C')
        caball = PI(i, j);
    }
  }
  pair<int, double> res = flors(tauler, caball.first, caball.second);
  if (res.first == 0)
    cout << "el cavall no pot arribar a cap flor" << endl;
  else {
    cout << "flors accessibles: " << res.first << endl;
    cout << "distancia mitjana: " << res.second << endl;
  }
}
