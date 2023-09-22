#include <iostream>
#include <vector>
using namespace std;

//Reverse of sequences

vector<int> read(int n) {
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    return v;
}

void inverse(vector<int>& v) {    
    bool primer = true;

    for (int i = v.size() - 1; i >= 0; --i) {
        if (not primer) cout << " ";
        else primer = false;
        cout << v[i];
        }

    cout << endl;
}

int main() {
    int n;

    while (cin >> n) {

        vector<int> v = read(n);
        inverse(v);
    }
}