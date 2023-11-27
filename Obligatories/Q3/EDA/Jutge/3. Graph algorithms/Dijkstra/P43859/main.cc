#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

struct Edge {
    int v, c;
    Edge(int vv, int cc): v(vv), c(cc) {}
};

typedef pair<int, int> P;
typedef vector<vector<P>> graph;

vector<int> dijkstra(const graph& g, int x) {
    int n = g.size();
    vector<int> dist(n, INT_MAX);
    vector<bool> visited (n, false);
    priority_queue<P, vector<P>, greater<P>> pq;
    dist[x] = 0;
    pq.push({dist[x], x});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (!visited[u]) {
            visited[u] = true;
            for (int i = 0; i < g[u].size(); ++i) {
                int v = g[u][i].first;
                int c = g[u][i].second;
                if (dist[v] > dist[u]+c) {
                    dist[v] = dist[u]+c;
                    pq.push(P({dist[v],v}));
                }
            }
        }
    }
    return dist;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        graph g(n);
        for (int i = 0; i < m; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            g[u].push_back(P({v,c}));
        }
        int x, y;
        cin >> x >> y;
        vector<int> d = dijkstra(g, x);
        if (d[y] == INT_MAX) cout << "no path from " << x << " to " << y << endl;
        else cout << d[y] << endl;
    }

}