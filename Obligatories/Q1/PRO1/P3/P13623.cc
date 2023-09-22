#include <iostream>
using namespace std;

int main () {
    int r, c;
    cin >> r >> c;

    int sum = 0;
    for (int i = 0; i < r; ++i){
        bool is_white = (i%2 == 0);
        for (int j = 0; j < c; ++j){
            char d;
            cin >> d;
            if (is_white) sum += d - '0';
            is_white = not is_white;
        }
    }
    cout << sum << endl;
}