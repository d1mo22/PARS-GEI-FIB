#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int x, n;
vector<int> monedes;

//Falla el formato de la salida
void escriu(const vector<int>& sol) {
    for (int i = 0; i < 2*n; ++i) cout << (sol[i] ? monedes[i] : '\0') << " ";
    cout << endl;
}

void combinacions(int idx, int suma, vector<int>& usado) {
    if (suma > x) return;
    if (idx == 2*n) {
        if (suma == x) escriu(usado);
    }
    else {
        usado[idx] = true;
        combinacions(idx+1, suma+monedes[idx], usado);
        usado[idx] = false;
        combinacions(idx+1, suma, usado);
    }
}

int main() {
    while (cin >> x >> n) {
        monedes = vector<int>(2*n);
        for (int i = 0; i < 2*n; i += 2) {
            cin >> monedes[i];
            monedes[i] = monedes[i+1]; 
        }
        sort(monedes.begin(), monedes.end());
        vector<int> usado(2*n, false);
        combinacions(0,0, usado);
        cout << "----------" << endl;
    }
}