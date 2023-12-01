#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector<vector<int>> VVB;
typedef vector<int> VB;

int n, m;
vector<char> especies;
VVB adj;
string solucion;
VB usado;

void combinacions(int idx) {
    if (idx == n) cout << solucion << endl;
    else {
        for (int i = 0; i < n; ++i) {
            char c = especies[i];
            if (!usado[c] and (idx == 0 or adj[c][solucion[idx-1]])) {
                solucion[idx] = c;
                usado[c] = true;
                combinacions(idx+1);
                usado[c] = false;
            }
        }
    }
}

int main() {
    cin >> n;
    especies = vector<char>(n);
    for (int i = 0; i < n; ++i) cin >> especies[i];
    cin >> m;
    adj = VVB(256, vector<int>(256,true));
    for (int i = 0; i < m; ++i) {
        char u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = false;
    }
    solucion = string(n, ' ');
    usado = VB(256, false);
    combinacions(0);

}