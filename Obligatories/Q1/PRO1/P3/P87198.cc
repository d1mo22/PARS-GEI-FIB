#include <iostream>
using namespace std;

int main () {
    int n;
    
    while (cin >> n){
        int spaces = n - 1;
        int cross = n;

        //part inicial del octogon
        for (int i = spaces; i > 0; --i){
            for (int j = 0; j < i; ++j) cout << " ";
            for (int j = 0; j < cross; ++j) cout << "X";
            cout << endl;
            cross += 2;
        }

        //part central del octogon
        for (int i = 0; i < n; ++i){
           for (int j = 0; j < cross; ++j) cout << "X"; 
           cout << endl;
        }

        //part final del octogon
        spaces = 1;
        cross -= 2;
        for (int i = spaces; i <= n - 1; ++i){
            for (int j = 0; j < i; ++j) cout << " ";
            for (int j = 0; j < cross; ++j) cout << "X";
            cout << endl;
            cross -= 2;
        } 
        cout << endl;
    }
}