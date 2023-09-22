#include <iostream>
using namespace std;

int main () {
    int a, b;
    cin >> a;
    b = 0;
    if (b <= a){
        while (b < a){
        cout << b*b*b << ",";
        ++b;              
        }
        cout << b*b*b << endl;
    }  
    else cout << endl;
}