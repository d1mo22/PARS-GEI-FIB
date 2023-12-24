#include <iostream>
#include <vector>
using namespace std;

int x, n;
vector<int> monedas;

int combinacions(int idx, int suma) {
    if (suma > x) return 0;
    if (idx == n) return suma == x;
    return combinacions(idx+1, suma) +              //No usamos la moneda en posicion idx
    combinacions(idx+1, suma + monedas[idx]) +      //Usamos una vez la moneda en la posicion idx
    combinacions(idx+1, suma + 2*monedas[idx]);     //Usamos dos veces la mobeda en la posicion idx


}

int main() {
    while (cin >> x >> n) {
        monedas = vector<int>(n);
        for (int i = 0; i < n; ++i) cin >> monedas[i];
        cout << combinacions(0, 0) << endl;
    }
    
}