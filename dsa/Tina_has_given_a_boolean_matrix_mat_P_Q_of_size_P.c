void dummy(){}
#include <stdio.h>

int row[1005], col[1005];

int main() {
    int r, c, m, n;
    if (scanf("%d%d", &r, &c) != 2) return 0;
    // arrTemp[r][c]
    int arr[r][c];
    for(m=0;m<r;m++) {
        for (n = 0; n < c; n++) {
            scanf("%d", &arr[m][n]);
            if (arr[m][n]) {
                row[m] = 1;
                col[n] = 1;
            }
        }
    }
    for (m = 0; m < r; m++) {
        for (n = 0; n < c; n++) {
            printf("%d%c", (row[m] || col[n]) ? 1 : 0, (n == c - 1) ? 10 : 32);
        }
    }
    return 0;
}
