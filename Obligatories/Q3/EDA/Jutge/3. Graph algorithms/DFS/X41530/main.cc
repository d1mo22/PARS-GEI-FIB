#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> graph;
typedef vector<int> VI;
typedef vector<bool> VB;

bool hay_ciclo(const graph& g, int u, VB& visitat, int ant) {
    bool ciclo;
    if (visitat[u]) ciclo = true;
    else {
        visitat[u] = true;
        ciclo = false;
        for (int i = 0; i < g[u].size() and !ciclo; ++i) {
            int adj = g[u][i];
            if (adj != ant)ciclo = hay_ciclo(g, adj, visitat, u);
        }
    }
    return ciclo;
}

int bosc(const graph& g) {
    int n_arb = 0;
    VB visitat(g.size(), false);
    bool cicle = false;
    int i = 0;
    while (i < g.size() and not cicle) {
        if (!visitat[i]) {
            if (hay_ciclo(g,i,visitat,-1)) cicle = true;
            else ++n_arb;
        }
        ++i;
    }
    if (cicle) return -1;
    return n_arb;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        graph g(n);
        int x, y;
        for (int i = 0; i < m; ++i) {
            cin >> x >> y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        int n_arb = bosc(g);
        if (n_arb == -1) cout << "no\n";
        else cout << n_arb << endl;
    }

}