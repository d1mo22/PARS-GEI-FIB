#include <iostream>
using namespace std;

int main () {
    int f, c; 
    int suma = 0;
    cin >> f >> c;

    for (int i = 0; i < f; ++i){
        for (int j = 0; j < c; ++j){
            char m;
            cin >> m;
            suma += m - '0';
        }
    } 
    cout << suma << endl;
}
