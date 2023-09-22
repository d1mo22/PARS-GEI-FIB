#include <iostream>
using namespace std;

int main () {
    int b, n;
    int count = 1;


    while (cin >> b >> n){
        while(n/b != 0){
            ++count;
            n = n/b;
        }
        cout << count << endl;
        count = 1;
    }
}