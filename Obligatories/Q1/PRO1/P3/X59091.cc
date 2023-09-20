#include <iostream>
using namespace std;

int main () {
    int n, m;
    bool first = true;
    while (cin >> n >> m){
        if (first) first = false;
        else cout << endl;
        int d = 9;
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                cout << d;
                --d;
                if (d < 0) d = 9;
            }
        cout << endl;
        }
    }
}