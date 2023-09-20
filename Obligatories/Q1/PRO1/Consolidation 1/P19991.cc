#include <iostream>
using namespace std;

int main() {
    int n;
    int suma = 0;
    cin >> n;
    char c;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cin >> c;

            if (i == j or (i + j) == n - 1) suma += (c - '0');   
        }
    }
    cout << suma << endl;
}