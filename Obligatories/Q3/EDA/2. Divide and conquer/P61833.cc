#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

Matrix operator%(const Matrix& a, int m) {
    Matrix c(2, vector<int>(2, 0));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0 ; j < 2; ++j) {
            c[i][j] = a[i][j]%m;
        }
    }
    return c;
}

Matrix operator*(const Matrix& a, const Matrix& b) {
    Matrix c(2, vector<int>(2, 0));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                c[i][j] += a[i][k]*b[k][j]; 
            }
        }
    }
    return c;
}

ostream& operator<<(ostream& os, const Matrix& a) {
    cout << a[0][0] << " " << a[0][1] << endl;
    cout << a[1][0] << " " << a[1][1] << endl;
    cout << "----------" << endl;
    return os;
}

Matrix pow(const Matrix& a, int n, int m) {
    if (n == 0) return {
        {1, 0},
        {0, 1}
    };
    Matrix c = pow(a, n/2, m);
    return (n%2 == 0) ? (c*c)%m : (a*c*c)%m;
}

int main() {
    Matrix a(2, vector<int> (2,0));
    int n, m;
    while (cin >> a[0][0] >> a[0][1] >> a[1][0] >> a[1][1] >> n >> m) {
        cout << pow(a, n, m);
    } 
    
}