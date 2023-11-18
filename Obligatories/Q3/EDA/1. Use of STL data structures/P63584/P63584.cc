#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef vector<int> VI; 
typedef vector<VI> VVI;

int k_esim(int k, const VVI& V) {
  map<int, int> min;
  for (int i = 0; i < V.size(); ++i) {
    if (!V[i].empty()) min[V[i][0]] = i;
  }
  pair<int, int> res;
  VI it(V.size(), 1);

  while (k > 0) {
    res.first = min.begin()->first;
    res.second = min.begin()->second;
    if (V[res.second].size() > it[res.second]) {
      int aux = V[res.second][it[res.second]++];
      min[aux] = res.second;
    }
    min.erase(min.begin());
    --k;
  }
  return res.first;
}


int main() {
  int n;
  while (cin >> n) {
    vector<vector<int> > V(n);
    int total = 0;
    for (int i = 0; i < n; ++i) {
      int m;
      cin >> m;
      total += m;
      V[i] = vector<int>(m);
      for (int j = 0; j < m; ++j) cin >> V[i][j];
    }

    int i1, i2, k;
    while (cin >> i1 >> i2 >> k, i1 != -1) {
      if (i1 < 0 or i1 >= n or i2 < 0 or i2 >= n or k < 1 or k > total) {
        cerr << "pifia!!! " << i1 << ' ' << i2 << ' ' << k << ' ' << n
             << ' ' << total << endl;
        return 0;
      }

      swap(V[i1], V[i2]);
      cout << k_esim(k, V) << endl;
    }
  }
}
