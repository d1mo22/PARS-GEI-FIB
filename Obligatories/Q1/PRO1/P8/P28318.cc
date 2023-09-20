#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<int> Row;
typedef vector<Row> Matrix;

Matrix read_matrix(int n, int m) {
    Matrix A (n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> A[i][j];
        }
    }
    return A;
}

void print_matrix(const Matrix& A) {
    int n = A.size();
    int m = A[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

void print_element(const Matrix& A) {
    int i, j;
    cin >> i >> j;
    cout << "element " << i << " " << j << ": " 
    << A[i - 1][j - 1] << endl;
}

void print_row(const Matrix& A) {
    int i;
    cin >> i;
    cout << "row " << i << ":";
    int m = A[0].size();
    for (int j = 0; j < m; ++j) cout << " " << A[i - 1][j];
    cout << endl;
}

void print_column(const Matrix& A) {
    int j;
    cin >> j;
    cout << "column " << j<< ":";
    int n = A.size();
    for (int i = 0; i < n; ++i) cout << " " << A[i][j - 1];
    cout << endl; 
}

void avalua(const Matrix& A) {
    string s;
    while (cin >> s) {
        if (s == "row") print_row(A);
        else if (s == "column") print_column(A); 
        else print_element(A);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    Matrix M = read_matrix(n, m);
    avalua(M);
}