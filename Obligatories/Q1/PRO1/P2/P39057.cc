#include <iostream>
#include <math.h>
using namespace std;

//Set decimal presision
//

int main () {
    cout.setf(ios::fixed);
    cout.precision(6);
    int n, i = 0;
    cin >> n; 
    while (i < n){
        string s;
        cin >> s;
        double a, b;
        if (s == "circle"){           
            cin >> a;
            cout << M_PI*a*a << endl;
        } 
        else if (s == ("rectangle")) {           
            cin >> a >> b;
            cout << a*b << endl;
        
        }
        ++i;
    } 
}

