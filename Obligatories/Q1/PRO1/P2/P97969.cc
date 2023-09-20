#include <iostream>
using namespace std;

int main () {
    char c;
    cin >> c;

    int count = 0;
    while (c != '.') {
        if (c == 'a') ++count ;
        cin >> c;
    }
    cout << count << endl;

}