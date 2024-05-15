#include <stdio.h>
#include <math.h>

int main() {
    int x = 665857;
    int y = 470832;

    int i = x*x*x*x;
    int j = 4*y*y*y*y;
    int k = 4*y*y;

    printf("%d\n", (i-j-k));
}