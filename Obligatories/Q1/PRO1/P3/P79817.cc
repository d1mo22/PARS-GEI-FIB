#include <iostream>
#include <math.h>
using namespace std;

int main () {
    int a, b, sum = 1;

    while (cin >> a >> b){
        if (b != 0){
            for (int i = 0; i < b; ++i){
                sum *= a;
            }
        }
        cout << sum << endl;
        sum = 1;
    }
    
}

