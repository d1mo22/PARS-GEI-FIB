#include <iostream>
#include <vector>
using namespace std;

int position_maximum(const vector<double>& v, int m) {
  double max = v[0];
  int pos = 0;
  for (int i = 1; i <= m; ++i) {
    if (v[i] > max) {
        max = v[i];
        pos = i;
    }
  }  
  return pos;
}

int main()
{
    int m, n;
    while (cin >> m >> n) {
        vector<double> V(n);
        for (int i = 0; i < n; ++i)
            cin >> V[i];
        cout << position_maximum(V, m) << endl;
    }
    return 0;
}
