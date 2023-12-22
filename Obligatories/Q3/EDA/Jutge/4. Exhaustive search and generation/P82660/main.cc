#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> numeros;
vector<int> usat;
int s, n;
int acabat;

void escriu() {
    if (!acabat) cout << "no solution" << endl;
    else {
        cout << '{';
        string aux = "";
        for (int i = 0; i < n; ++i) {
            if (usat[i]) {
                cout << aux << numeros[i];
                aux = ",";
            }  
        }
        cout << '}' << endl;
    }
}

void combinacions(int idx, int suma) {
    if (idx == n) {
        if (suma == s) {
            acabat = true;
        }
    }

    else {
        if (!acabat) {
            usat[idx] = true;
            combinacions(idx+1, suma+numeros[idx]);
        }
        if (!acabat) {
            usat[idx] = false;
            combinacions(idx+1, suma);
        }
        
    }
}

int main() {
    cin >> s >> n;
    numeros = vector<int>(n);
    for (int i = 0; i < n; ++i) cin >> numeros[i];
    sort(numeros.begin(), numeros.end(), greater<int>());
    usat = vector<int>(n, false);
    acabat = false;
    combinacions(0, 0);
    escriu();
}