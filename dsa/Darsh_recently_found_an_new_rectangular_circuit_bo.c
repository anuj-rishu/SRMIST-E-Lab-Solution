void dummy(){}
#include <stdio.h>
#include <stdbool.h>

int A[309][309];
bool ok[309][309][309];

int main() {
    int T, R, C, L, i, j, k;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        scanf("%d%d%d", &R, &C, &L);
        for (i = 0; i < R; i++)
            for (j = 0; j < C; j++)
                scanf("%d", &A[i][j]);

        for (i = 0; i < R; i++) {
            for (j = 0; j < C; j++) {
                int mn = A[i][j], mx = A[i][j];
                for (k = j; k < C; k++) {
                    if (A[i][k] < mn) mn = A[i][k];
                    if (A[i][k] > mx) mx = A[i][k];
                    ok[i][j][k] = (mx - mn <= L);
                }
            }
        }

        int ans = 0;
        for (j = 0; j < C; j++) {
            for (k = j; k < C; k++) {
                int cur = 0, w = k - j + 1;
                for (i = 0; i < R; i++) {
                    if (ok[i][j][k]) {
                        cur++;
                        if (cur * w > ans) ans = cur * w;
                    } else cur = 0;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
