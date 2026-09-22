#include <stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n<=0 || n>=66 || m<=0 || m>=99) {
        printf("Invalid\n");
        return 0;
    }
    int P[101][101], A[101][101];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &P[i][j]);
    int count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &A[i][j]);
            if (A[i][j] != 0) count++;
        }
    }
    printf("%d\n", count);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (A[i][j] != 0)
                printf("%d %d %d %d %d\n", i, j, i, j, P[i][j] - A[i][j]);
        }
    }
}
