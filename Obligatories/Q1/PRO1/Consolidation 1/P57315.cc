#include <iostream>
using namespace std;

int main() {
    int a, b, c, max, min, med;
    cin >> a >> b >> c;
    string s;
    cin >> s;

    if (a >= b and a >= c) {
        max = a;
        
        if (b >= c) {
            med = b;
            min = c; 
        }

        else {
            med = c;
            min = b;
        }
    }

    else if (b >= a and b >= c){
        max = b;

        if (a >= c){
            med = a;
            min = c;
        }

        else {
            med = c;
            min = a;
        }
    } 

    else {
        max = c;

        if (a >= b) {
            med = a;
            min = b;
        }

        else {
            med = b;
            min = a;
        }
    }

    if (s == "ABC") cout << min << " " << med << " " << max << endl;
    else if (s == "ACB") cout << min << " " << max << " " << med << endl;
    else if (s == "BAC") cout << med << " " << min << " " << max << endl;
    else if (s == "BCA") cout << med << " " << max << " " << min << endl;
    else if (s == "CAB") cout << max << " " << min << " " << med << endl;
    else cout << max << " " << med << " " << min << endl;

    
}