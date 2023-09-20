#include <iostream>
#include <vector>
using namespace std;

//Counting frequences

const int MIN = 1000000000;
const int MAX = 1000001000;

void print_stats(const vector<int>& stats) {
    int n = stats.size();
    for (int i = 0; i < n; ++i) {
        if (stats[i] > 0) cout << MIN + i << " : " 
        << stats[i] << endl;
    }
}

void calculate_stats(int n) {
    vector<int> stats(MAX - MIN + 1, 0);
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        ++stats[num - MIN];
    }
    print_stats(stats);
}

int main() {
    int n;
    cin >> n;
    calculate_stats(n);
}