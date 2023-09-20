#include <iostream>
using namespace std;

int main() {
    cout.setf(ios::fixed);
    cout.precision(4);
    
    int n; 
    cin >> n; 

    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;

        double seq1, seq, max, min, avg;
        cin >> seq1;

        min = seq1;
        max = seq1;
        avg = seq1;
        for (int j = 1; j < m; ++j) {
            cin >> seq;
            if (seq < min) min = seq;
            if (seq > max) max = seq;
            avg += seq;
        }
        cout << min << " " << max << " " << avg/m << endl;
    }
}

