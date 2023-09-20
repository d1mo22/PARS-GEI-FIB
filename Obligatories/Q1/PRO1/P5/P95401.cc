#include <iostream>
using namespace std;


bool is_leap_year(int year) {
    if (year%100 != 0 and year%4 == 0) return true;
    else if ((year/100)%4 == 0 and year%4 == 0) return true;
    else return false;
}


int main() {
    int a;
    while (cin >> a) cout << (is_leap_year(a) ? "true" : "false") << endl;
}
