#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int count = 0;
        int left, right;
        cin >> left;

        while (left != 0) {
            cin >> right;
            if (right > left) ++count;

            left = right;   
        }
        cout << count << endl;
    }
}