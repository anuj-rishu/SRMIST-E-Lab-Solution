#include <stdio.h>

int smaller(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) return printf("Invalid Input\n") * 0;
    if (n < 1 || n > 50 || m < 1 || m > 50) return printf("Invalid Input\n") * 0;
    int A[55][55], non_zero = 0, total = 0, v2 = 0, x, i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) {
            if (scanf("%d", &A[i][j]) != 1) return printf("Invalid Input\n") * 0;
            if (A[i][j] > 0) total += A[i][j], non_zero++;
        }
    for (i = 0; i < n; i++) {
        x = A[i][0];
        for (j = 1; j < m; j++) {
            v2 += smaller(x, A[i][j]) * 2;
            x = A[i][j];
        }
    }
    for (j = 0; j < m; j++) {
        x = A[0][j];
        for (i = 1; i < n; i++) {
            v2 += smaller(x, A[i][j]) * 2;
            x = A[i][j];
        }
    }
    printf("%d\n", non_zero * 2 + total * 4 - v2);
}
