#include <iostream>
#include <stack>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;
typedef pair<int, int> PI;

const PI moviments[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool pos_ok(const VVC &tauler, int i, int j, int n, int m) {
  return ((i >= 0) and (i < n) and (j >= 0) and (j < m) and
          (tauler[i][j] != 'X'));
}

void bloquejar_monstres(VVC &tauler, vector<PI> monstres, int n, int m) {
  for (PI pos : monstres) {
    int i = pos.first;
    int j = pos.second;
    for (PI mov : moviments) {
      int ii = i + mov.first;
      int jj = j + mov.second;
      if (pos_ok(tauler, ii, jj, n, m))
        tauler[ii][jj] = 'X';
    }
  }
}

bool DFS(VVC &tauler, const PI &inici, const PI &final, int n, int m) {
  stack<PI> q;
  q.push(inici);

  while (!q.empty()) {
    PI pos = q.top();
    q.pop();

    if (pos == final)
      return true;

    for (PI mov : moviments) {
      int i = pos.first + mov.first;
      int j = pos.second + mov.second;
      if (pos_ok(tauler, i, j, n, m)) {
        q.push(PI(i, j));
        tauler[pos.first][pos.second] = 'X';
      }
    }
  }
  return false;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    VVC tauler(n, VC(m));
    vector<PI> monstres;
    PI inici, final;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        char c;
        cin >> c;
        if (c == 'M')
          monstres.push_back(PI(i, j));
        else if (c == 'I')
          inici = PI(i, j);
        else if (c == 'F')
          final = PI(i, j);
        tauler[i][j] = c;
      }
    bloquejar_monstres(tauler, monstres, n, m);
    cout << (DFS(tauler, inici, final, n, m) ? "SI" : "NO") << endl;
  }
}
