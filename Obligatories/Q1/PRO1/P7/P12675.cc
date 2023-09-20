#include <iostream>
#include <vector>
using namespace std;

//Common elements

int common_elements (const vector<int>& X, const vector<int>& Y) {
    int n = X.size();
    int m = Y.size();
    int i = 0;
    int j = 0;
    int count = 0;

    while (i < n and j < m) {
        if (X[i] == Y[j]) {
            ++count;
            ++i;
            ++j;
        } 
        else if (X[i] > Y[j]) ++j;
        else ++i;
    }
    return count;
}


int main () {
    int n, m;
    while (cin >> m >> n) {

        vector<int> X(m);
        for (int i=0; i<m; ++i) cin >> X[i];

        vector<int> Y(n);
        for (int i=0; i<n; ++i) cin >> Y[i];

        cout << common_elements(X,Y) << endl;

    }
    return 0;
}

