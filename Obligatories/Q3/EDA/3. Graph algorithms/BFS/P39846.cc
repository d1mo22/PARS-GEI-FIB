//Treasures 4 (BFS) iterativo
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using Graf = vector<vector<char>>;
using VVI = vector<vector<int>>;
using pos = pair<int,int>;
const pos DIR[4] = {{-1,0}, {1,0}, {0,1}, {0,-1}};

bool within_range(int i, int j, int n, int m) {
    return (i >= 0) and (i < n) and (j >= 0) and (j < m);
}

int bfs(const Graf& g, int r, int c) {
    int n = g.size();
    int m = g[0].size();
    int d = -1;
    queue<pos> q;
    VVI distancia(n, vector<int>(m,-1));
    q.push({r,c});
    distancia[r][c] = 0;
    while(not q.empty()) {
        pos p = q.front(); 
        q.pop();
        int i = p.first;
        int j = p.second;
        if (g[i][j] == 't') {
            if (d < distancia[i][j]) d = distancia[i][j];
        }
        for (int k = 0; k < 4; ++k) {
            int ii = i+DIR[k].first;
            int jj = j+DIR[k].second;
            if (within_range(ii, jj, n, m) and g[ii][jj] != 'X' and distancia[ii][jj] == -1) {
                q.push({ii,jj});
                distancia[ii][jj] = 1 + distancia[i][j];
            }
        }
    }
    return d;
}
    


int main() {
    int files, columnes;
    cin >> files >> columnes;
    Graf g(files, vector<char>(columnes));

    for (int i = 0; i < files; ++i) {
        for (int j = 0; j < columnes; ++j) {
            cin >> g[i][j];
        }
    }

    int r, c;
    cin >> r >> c;

    int num = bfs(g, r-1, c-1);
    if (num == -1) cout << "no treasure can be reached\n";
    else cout << "maximum distance: " << num << endl;
}