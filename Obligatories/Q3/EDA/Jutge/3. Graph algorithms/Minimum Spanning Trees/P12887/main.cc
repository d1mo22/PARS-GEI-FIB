#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int,int> P;
typedef pair<int,P> Edge;
typedef vector<vector<P>> graph;

void mst(const graph& g) {
    int n = g.size();
    vector<bool> used(n, false);
    priority_queue<Edge, vector<Edge>, greater<Edge>> q;
    int suma = 0;
    q.push({0,{0,0}});
    while (!q.empty()) {
        int p = q.top().first;
        int u = q.top().second.first;
        int v = q.top().second.second;
        q.pop();
        if (!used[v]) {
            used[v] = true;
            suma += p;
            for (auto e : g[v]) {
                int pes = e.first;
                int vertex = e.second;
                q.push({pes,{v,vertex}});
            }
        }
    }
    cout << suma << endl;
}

int main() {
    int n, m;
    while(cin >> n >> m) {
        graph g(n);
        for(int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u; --v;
            g[u].push_back({w,v});
            g[v].push_back({w,u});        
        }
        mst(g);
    } 
}