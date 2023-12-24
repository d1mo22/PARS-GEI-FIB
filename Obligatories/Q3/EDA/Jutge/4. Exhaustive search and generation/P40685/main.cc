#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> VI;

int n, x;
VI valors;
VI usat;

void escriu() {
    cout << '{';
    string aux = "";
    for (int i = 0; i < n; ++i) {
        if (usat[i]) {
            cout << aux << valors[i];
            aux = ",";
        }  
    }
    cout << '}' << endl;
}

void combinacions(int idx, int suma) {
    if (idx == n) {
        if (suma == x) escriu();
    }
    else {
        usat[idx] = true;
        combinacions(idx+1, suma+valors[idx]);
        usat[idx] = false;
        combinacions(idx+1, suma);
    }
}

int main() {
    cin >> x >> n;
    valors = usat = VI(n);
    for (int i = 0; i < n; ++i) cin >> valors[i];
    combinacions(0, 0);
}