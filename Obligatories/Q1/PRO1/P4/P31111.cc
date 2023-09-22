#include <iostream>
using namespace std;

int main() {
    char c;
    int balance = 0;

    while (cin >> c and balance >= 0) {
        if (c == '(') ++balance;
        else if (c == ')') --balance;
    }
    
    if (balance == 0) cout << "yes" << endl;
    else cout << "no" << endl;
     
}