#include <iostream>
using namespace std;

int main () {
    int n;
    int count = 0;

    while (cin >> n){
        while (n != 1){
            if (n%2 == 0){
                n = n/2;
                ++count;
        }
            else if (n%2 != 0) {
                n = (n*3)+1;
                ++count;
        } 
        }
        cout << count << endl;
        count = 0;
    }
}