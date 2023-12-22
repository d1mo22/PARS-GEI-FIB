#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

int n, r;
VVI tauler;

bool pos_ok(int i, int j) {
  return ((i >= 0) and (i < n) and (j >= 0) and (j < n));
}

bool possible(int x, int y) {
  for (int i = x - 1; i <= x + 1; ++i)
    for (int j = y - 1; j <= y + 1; ++j) {
      if (pos_ok(i, j) and tauler[i][j])
        return false;
    }
  return true;
}

void print_tauler() {
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      cout << (tauler[x][y] ? "K" : ".");
    }
    cout << endl;
  }
  cout << "----------" << endl;
}

void move(int i, int j, int &ii, int &jj) {
  if (j < n - 1) {
    ii = i;
    jj = j + 1;
  } else {
    ii = i + 1;
    jj = 0;
  }
}

void reis(int i, int j, int numero) {
  if (numero == r)
    print_tauler();
  else if (i != n) {
    int ii, jj;
    move(i, j, ii, jj);

    if (possible(i, j)) {
      tauler[i][j] = true;
      reis(ii, jj, numero + 1);
    }
    tauler[i][j] = false;
    reis(ii, jj, numero);
  }
}

int main() {
  cin >> n >> r;
  tauler = VVI(n, VI(n, false));
  reis(0, 0, 0);
}
