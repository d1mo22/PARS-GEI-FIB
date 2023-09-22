#include <iostream>
using namespace std;

int max2(int a, int b) {
    if (a > b) return a;
    return b;
}

int max4(int a, int b, int c, int d){
    return max2(max2(a, b), max2(c, d));
}


int main() {
    int a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        cout << max4(a, b, c, d) << endl;
}   }
