#include <vector>
#include <iostream>
using namespace std;


typedef vector< vector<int> > Matrix;

Matrix product(const Matrix& A, const Matrix& B) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();
    Matrix c(m, vector<int> (p));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) c[i][j] += A[i][k]*B[k][j];
        }
    }
    return c;
}