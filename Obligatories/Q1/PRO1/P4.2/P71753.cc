#include <iostream>
using namespace std;

int main() {

    int n, seq1, seq, max;

    while (cin >> n) {
        cin >> seq1;
        max = seq1;

        for (int i = 1; i < n; ++i) {
            cin >> seq;
            if (seq > max) max = seq;
        }
        cout << max << endl;
    }
}