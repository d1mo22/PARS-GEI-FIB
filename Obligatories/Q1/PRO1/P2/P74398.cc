#include <iostream>
using namespace std;

const int MAX_BASE = 16;

int main () {
    int k;
    cin >> k;

    for (int base = 2; base <= MAX_BASE; ++base){
        int num = k;
        int digits = 1;
        while (num >= base){
            num /= base;
            ++digits;
        }
        cout << "Base " << base << ": " 
        << digits << " cifras." << endl;
    }
    
}