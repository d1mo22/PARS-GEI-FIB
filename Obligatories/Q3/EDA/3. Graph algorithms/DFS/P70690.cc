//Treasures 1 (DFS) iterativo
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

using Graf = vector<vector<char>>;
using VVB = vector<vector<bool>>;
using pos = pair<int,int>;
const pos DIR[4] = {{-1,0}, {1,0}, {0,1}, {0,-1}};

bool within_range(int i, int j, int n, int m) {
    return (i >= 0) and (i < n) and (j >= 0) and (j < m);
}

bool dfs(const Graf& g, int r, int c) {
    int n = g.size();
    int m = g[0].size();
    stack<pos> s;
    VVB visitats(n, vector<bool>(m,false));
    s.push({r,c});
    while(!s.empty()) {
        pos p = s.top(); 
        s.pop();
        int i = p.first;
        int j = p.second;
        if (!visitats[i][j]) {
            visitats[i][j] = true;
            if (g[i][j] == 't') return true;
            for (int k = 0; k < 4; ++k) {
                int ii = i+DIR[k].first;
                int jj = j+DIR[k].second;
                if (within_range(ii, jj, n, m) and g[ii][jj] != 'X') s.push({ii,jj});
            }
        }
    }
    return false;
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

    cout << (dfs(g, r-1, c-1) ? "yes" : "no") << endl;
}