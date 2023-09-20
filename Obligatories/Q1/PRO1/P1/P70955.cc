#include <iostream>
using namespace std;

int main () {
    int y, d, h, m, s;
    cin >> y >> d >> h >> m >> s;
    cout << (y * 31536000) + (d * 86400) + 
    (h * 3600) + (m * 60) + s << endl;
}