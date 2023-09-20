#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int count = 1;
    int aux = n;
    int sum_r = 0;
    int sum_l = 0;

    while (aux/10 != 0) {
        ++count;
        aux /= 10;
    }

    if (count%2 == 0) {
        for (int i = 0; i < count/2; ++i){
            sum_r += n%10;
            n /= 10;
        }
        for (int i = 0; i < count/2; ++i){
            sum_l += n%10;
            n /= 10;
        }

        if (sum_l > sum_r) cout << sum_l << " > " << sum_r << endl;
        else if (sum_l < sum_r) cout << sum_l << " < " << sum_r << endl;
        else cout << sum_l << " = " << sum_r << endl;

    }
    else cout << "nothing" << endl;
}