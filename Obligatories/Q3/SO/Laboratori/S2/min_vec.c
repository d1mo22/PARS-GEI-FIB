#include <stdio.h>
#include <string.h>

int min(int* A, int size_A) {
    int n = size_A;
    int m = A[0];
    for (int i = 0; i < n; ++i) if (A[i] < m) m = A[i];
    return m;
}