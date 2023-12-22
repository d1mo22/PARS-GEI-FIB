#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PI;

int n, m;
PI obj;
VVC graph;
VVI visitat;

const int I[4] = {1, 0, -1, 0};
const int J[4] = {0, 1, 0, -1};

bool pos_ok(int i, int j) {
  return ((i >= 0) and (i < n) and (j >= 0) and (j < m));
}

void escriu_paraula(const VC &paraula) {
  int l = paraula.size();
  for (int i = 0; i < l; ++i)
    cout << paraula[i];
  cout << endl;
}

void combinacions(int x, int y, VC &paraula) {
  if (x == obj.first and y == obj.second) {
    escriu_paraula(paraula);
  } else {
    for (int i = 0; i < 4; ++i) {
      int ii = x + I[i];
      int jj = y + J[i];
      if (pos_ok(ii, jj) and !visitat[ii][jj]) {
        visitat[ii][jj] = true;
        paraula.push_back(graph[ii][jj]);
        combinacions(ii, jj, paraula);
        paraula.pop_back();
        visitat[ii][jj] = false;
      }
    }
  }
}

int main() {
  cin >> n >> m;
  graph = VVC(n, VC(m));
  visitat = VVI(n, VI(m, false));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> graph[i][j];
  PI start;
  cin >> start.first >> start.second;
  cin >> obj.first >> obj.second;
  VC paraula;
  paraula.push_back(graph[start.first][start.second]);
  visitat[start.first][start.second] = true;
  combinacions(start.first, start.second, paraula);
}
