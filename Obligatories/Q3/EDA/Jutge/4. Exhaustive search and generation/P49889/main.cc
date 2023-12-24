#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<vector<int>> VVI;

void combinaciones(int idx, string& solucion, const vector<string>& letras, VVI& usado, int m) {
    if (idx == m) cout << solucion << endl;
    else {
        int k2 = idx%2;
        for (int i = 0; i < m/2; ++i) {
            if (!usado[k2][i]) {
                solucion[idx] = letras[k2][i];
                usado[k2][i] = true;
                combinaciones(idx+1, solucion, letras, usado, m);
                usado[k2][i] = false;
            }
        }
    }
        
}


int main() {
    int n; cin >> n;
    vector<string> letras(2);
    cin >> letras[0] >> letras[1];
    string solucion = string(2*n, ' ');
    VVI usado(2, vector<int> (n,false));
    combinaciones(0, solucion, letras, usado, 2*n);
}