#include <iostream>
using namespace std;

int main() {
    int f, c;
    cin >> f >> c;

    for (int i = 0; i < f; ++i) {

        int d = -i;

        for (int j = 0; j < c; ++j) {

            if (d < 0) cout << (-d)%10;
            else cout << d%10;
            ++d;
        }
        cout << endl;
    }
}
