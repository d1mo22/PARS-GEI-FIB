#include <iostream>
using namespace std;

int main() {
    int n;
    int k = 0;
    
    while (cin >> n){
        if (k == 0) k = 1;
        else cout << endl;

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                cout << n;
            }
            cout << endl;
        }       
    }
}