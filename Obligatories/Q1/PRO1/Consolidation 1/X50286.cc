#include <iostream>
using namespace std;

int main() {
    string s;
    int count = 0;
    
    while (cin >> s){
        if (s == "hello") ++count;
    }
    cout << count << endl;
}