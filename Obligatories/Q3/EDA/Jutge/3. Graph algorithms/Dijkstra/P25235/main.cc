#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

struct Edge {
    int v, c;
    Edge(int vv, int cc) : v(vv), c(cc) {}
};

typedef pair<vector<int>,vector<int>> PV;
typedef pair<pair<int,int>,int> PP;
typedef vector<vector<Edge>> graph;

PV dijkstra(const graph& g, int s) {
    int n = g.size();
    vector<int> dist(n, INT_MAX);
    vector<int> pasos(n, -1);
    vector<bool> visited(n, false);
    priority_queue<PP, vector<PP>, greater<PP>> pq;
    dist[s] = 0;
    pasos[s] = 1;
    pq.push({{dist[s],pasos[s]},s});
    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if(!visited[u]) {
            visited[u] = true;
            for (Edge e: g[u]) {
                int v = e.v;
                int c = e.c;
                if ((dist[v] > dist[u] + c) or (dist[v] == dist[u] + c and pasos[v] > pasos[u] + 1)) {
                    dist[v] = dist[u] + c;
                    pasos[v] = pasos[u] + 1;
                    pq.push({{dist[v], pasos[v]},v});
                }
            }
        }
    }
    return {dist, pasos};
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        graph g(n);
        for (int i = 0; i < m; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            g[u].push_back(Edge(v,c));
        }
        int x, y;
        cin >> x >> y;
        PV d = dijkstra(g, x);
        if (d.first[y] == INT_MAX) cout << "no path from " << x << " to " << y << endl;
        else {
            vector<int> recorido;
            for (int i = y; i != -1; i = d.second[i]) recorido.push_back(i);
            for (int k = recorido.size()-1; k > 0; --k) cout << recorido[k] << " ";
            cout << y << endl;
        }
    }
}