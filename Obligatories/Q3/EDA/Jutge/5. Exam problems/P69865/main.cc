#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;
typedef pair<int, int> PI;

void escriure_tauler(const VVC &tauler) {
  int n = tauler.size();
  int m = tauler[0].size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j)
      cout << tauler[i][j];
    cout << endl;
  }
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    vector<PI> caballs;
    vector<PI> alfils;
    vector<PI> trampes;
    VVC tauler(n, VC(m));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        char c;
        cin >> c;
        if (c == 'B')
          alfils.push_back(make_pair(i, j));
        else if (c == 'K')
          caballs.push_back(make_pair(i, j));
        else if (c == 'T')
          trampes.push_back(make_pair(i, j));
        tauler[i][j] = c;
      }
    escriure_tauler(tauler);
    cout << endl;
  }
}
