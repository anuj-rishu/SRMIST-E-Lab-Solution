#include <stdio.h>
#include <stdlib.h>

#define N 100

static int aa[N], dp[N][N];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int n, k, i, j, t, a;
    scanf("%d%d", &n, &k);
    if(n > 10 || k>10) {
        printf("Invaild.\n");
        return 0;
    }

    for (i = 0; i < n; i++)
        scanf("%d", &aa[i]);

    qsort(aa, n, sizeof *aa, cmp);

    for (i = 0; i < n; i++) {
        j = 0;
        while (aa[i] - aa[j] > 5) j++;
        for (t = 1; t <= k; t++) {
            a = dp[j][t - 1] + i - j + 1;
            dp[i + 1][t] = a > dp[i][t] ? a : dp[i][t];
        }
    }

    printf("%d\n", dp[n][k]);
    return 0;
}
