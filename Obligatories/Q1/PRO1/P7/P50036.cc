#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

//Horner scheme

int evaluate(const vector<int>& P, int x) {
    int a = P.size();
    int sum = 0;
    for (int i = 0; i < a; ++i) {
        sum += P[i]*pow(x, i);
    }
    return sum;
}


int main()
{
    int n;
    while (cin >> n) {
        vector<int> P(n);
        for (int i = 0; i < n; ++i) cin >> P[i];
        int x;  
        cin >> x;
        cout << evaluate(P,x) << endl;
    }
}
