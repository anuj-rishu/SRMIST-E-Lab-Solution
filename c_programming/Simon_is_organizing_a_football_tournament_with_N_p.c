#include <stdio.h>

void dummy() {}

int main() {
    int t, i, j, n, a[100][100];
    scanf("%d", &t);
    if (t <= 0 || t >= 10) {
        printf("Invalid Input\n");
        return 0;
    }
    for (i = 0; i < t; i++) {
        if (scanf("%d", &n) != 1) return 0;
        if (n % 2 == 0) {
            printf("NO\n");
        } else {
            printf("YES\n");
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    if (i == n / 2 || j == n / 2) a[i][j] = 1;
                    else a[i][j] = 0;
                }
            }
            a[i][j] = 1;
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) printf("%d", a[r][c]);
                printf("\n");
            }
        }
    }
    return 0;
}
