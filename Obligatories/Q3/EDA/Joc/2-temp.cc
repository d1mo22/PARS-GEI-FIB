#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v(3, 1);
    v.resize(2);
    for (int i : v) cout << i << endl;
}