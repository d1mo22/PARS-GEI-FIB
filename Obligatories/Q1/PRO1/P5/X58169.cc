#include <iostream>
using namespace std;

void infoSequencia(int& max, int& lpos) {
    if (lpos > max) max = lpos;
}

int main() {
    int n;
    int count = 0;
    int max = 0;
    int pos = 0; 
    int lpos = 0;

    while (cin >> n and n != 0) {
        lpos = n;
        infoSequencia(max, lpos);
        ++count;
        if (max == lpos) pos = count;
    }
    
    int m;
    int pos2 = 1;

    while (cin >> m and m != max and m != 0) {
        ++pos2;
    }

    if (m == max) cout << max << " " << pos << " " << pos2 << endl;
    else cout << max << " " << pos << " " << "-" << endl;
}