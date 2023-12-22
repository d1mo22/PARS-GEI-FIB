#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;

VI numeros, usat;
int s, n;

void escriu() {
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

void combinacions(int idx, int suma, int total) {
    if (suma > s) return;

    if (suma + total < s) return;
    
    if (idx == n) {
        if (suma == s) escriu();
    }

    else {
        usat[idx] = true;
        combinacions(idx+1, suma+numeros[idx], total - numeros[idx]);
        usat[idx] = false;
        combinacions(idx+1, suma, total - numeros[idx]);
    }
}

int main() {
    int total = 0;
    cin >> s >> n;
    numeros = usat = VI(n, false);
    for (int i = 0; i < n; ++i)  {
        cin >> numeros[i];
        total += numeros[i];
    }
    combinacions(0,0, total);
}