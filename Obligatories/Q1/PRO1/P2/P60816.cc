#include <iostream>
using namespace std;

int main () {
    int a;
    char b;
    cin >> a;
    if (a < 10) cout << a << endl;
    else if (a <= 15){
        b = a + 55;
        cout << b << endl;
    }
    else {
        while (a/16 != 0){
        if (a%16 < 10) b = a%16 + 48;
        else b = a%16 + 55;
    cout << b;
    a = a/16;
    }
    cout << a << endl;
  }
}