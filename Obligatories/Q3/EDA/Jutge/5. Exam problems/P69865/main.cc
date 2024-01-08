#include <iostream>
#include <vector>
using namespace std;

struct Point {
  int r, c;
  Point(int rr, int cc) : r(rr), c(cc) {}
};

bool ok(int n, int m, const Point &p) {
  return (0 <= p.r) and (p.r < n) and (0 <= p.c) and (p.c < m);
}

const int N_DIRS_KNIGHT = 8;
const int DR_KNIGHT[8] = {-2, -1, 2, 1, -2, -1, 2, 1};
const int DC_KNIGHT[8] = {-1, -2, -1, -2, 1, 2, 1, 2};
const int N_DIRS_BISHOP = 4;
const int DR_BISHOP[4] = {1, -1, 1, -1};
const int DC_BISHOP[4] = {1, 1, -1, -1};

int dfs(int n, int m, const Point &p, vector<vector<char>> &map,
        vector<vector<bool>> &marked, const int N_DIRS, const int DR[],
        const int DC[]) {
  int s = 0;
  marked[p.r][p.c] = true;
  for (int i = 0; i < N_DIRS; ++i) {
    Point q(p.r + DR[i], p.c + DC[i]);
    if (ok(n, m, q) and map[q.r][q.c] != 'T' and not marked[q.r][q.c])
      s += dfs(n, m, q, map, marked, N_DIRS, DR, DC);
  }
  if ('0' <= map[p.r][p.c] and map[p.r][p.c] <= '9') {
    s += map[p.r][p.c] - '0';
    map[p.r][p.c] = '.';
  }
  return s;
}
int main(void) {
  int n, m;
  while (cin >> n >> m) {
    vector<Point> knights, bishops;
    vector<vector<char>> map(n, vector<char>(m));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        cin >> map[i][j];
        switch (map[i][j]) {
        case 'K':
          knights.push_back(Point(i, j));
          break;
        case 'B':
          bishops.push_back(Point(i, j));
          break;
        }
      };
    int s = 0;
    vector<vector<bool>> marked_knight(n, vector<bool>(m, false));
    for (int k = 0; k < knights.size(); ++k) {
      Point p = knights[k];
      if (not marked_knight[p.r][p.c])
        s += dfs(n, m, p, map, marked_knight, N_DIRS_KNIGHT, DR_KNIGHT,
                 DC_KNIGHT);
    }
    vector<vector<bool>> marked_bishop(n, vector<bool>(m, false));
    for (int k = 0; k < bishops.size(); ++k) {
      Point p = bishops[k];
      if (not marked_bishop[p.r][p.c])
        s += dfs(n, m, p, map, marked_bishop, N_DIRS_BISHOP, DR_BISHOP,
                 DC_BISHOP);
    }
    cout << s << endl;
  }
}
