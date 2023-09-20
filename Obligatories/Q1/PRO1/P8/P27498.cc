#include <iostream>
#include <vector>
using namespace std;

typedef vector <vector<int>> Matrix;

void transpose(Matrix& M) {
    int n = M.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            swap(M[i][j], M[j][i]);
        }
    }
}
