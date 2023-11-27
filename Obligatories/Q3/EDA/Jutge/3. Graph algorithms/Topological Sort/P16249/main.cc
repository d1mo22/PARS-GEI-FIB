#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
using namespace  std;

typedef vector<vector<int>> graph;
typedef vector<int> VI;
typedef vector<string> VS;

queue<string> topologic(const graph& g, map<string,int>& paraules, const VS& nombres, VI& grau) {
    int n = g.size();
    priority_queue<string, VS, greater<string>> pq;
    for (int i = 0; i < n; ++i) if (grau[i] == 0) pq.push(nombres[i]);

    queue<string> ordre;
    while(!pq.empty()) {
        string s = pq.top();
        pq.pop();
        ordre.push(s);
        int u = paraules[s];
        for (int v : g[u]) {
            if (--grau[v] == 0) pq.push(nombres[v]);
        }
    }
    return ordre;
}

void write(queue<string> q) {
    while (!q.empty()) {
        cout << q.front();
        q.pop();
    }
    cout << endl;
} 


int main() {
    int n, m;
    while (cin >> n) {
        map<string,int> paraules;
        VS nombres(n);
        for (int i = 0; i < n; ++i) {
            string a;
            cin >> a;
            nombres[i] = a;
            paraules.insert({a, i});
        }
        cin >> m;
        graph g(n);
        VI grau(n, 0);
        for (int i = 0; i < m; ++i) {
            string x, y;
            cin >> x >> y;
            g[paraules[x]].push_back(paraules[y]);
            ++grau[paraules[y]];
        }
        queue<string> ordre = topologic(g, paraules, nombres, grau);

        if (ordre.size() == nombres.size()) write(ordre);
        else cout << "NO VALID ORDERING\n";
    }
}