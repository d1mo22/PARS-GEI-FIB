#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<char> VC;
typedef vector<VC> VVC;

int x;
const pair<int, int> move[4] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

int main() {
  cin >> x;
  for (int i = 0; i < x; ++i) {
    int n, m;
    cin >> n >> m;
    VVC tauler(n, VC(m));
    for (int j = 0; j < n; ++j)
      for (int k = 0; k < m; ++k)
        cin >> tauler[j][k];
  }
}
