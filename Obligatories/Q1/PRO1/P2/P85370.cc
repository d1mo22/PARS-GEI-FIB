#include <iostream>
#include <math.h>
using namespace std;

int main () {
    cout.setf(ios::fixed);
    cout.precision(4);

    double c, t, i;
    string s;
    cin >> c >> i >> t >> s;

    if (s == "simple"){
        cout << c+(c*(i/100)*t) << endl;
    }

    else if (s == "compost") {
        cout << c*pow((1+(i/100)),t) << endl;
    }   
}