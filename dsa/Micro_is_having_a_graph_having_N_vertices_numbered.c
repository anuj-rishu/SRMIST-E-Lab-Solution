#include <stdio.h>
#include <string.h>
int d[1024][10], a[10][10];

int main() {
    int n, m, u, v, i, j, k, ans = 0, t = 1;
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d", &u, &v);
        a[u - 1][v - 1] = a[v - 1][u - 1] = 1;
    }
    while (t--) {
        for (i = 0; i < n; i++)
            d[1 << i][i] = 1;
        for (i = 1; i < (1 << n); i++)
            for (j = 0; j < n; j++)
                if (d[i][j])
                    for (k = 0; k < n; k++)
                        if (a[j][k] && !(i >> k & 1))
                            d[i | 1 << k][k] += d[i][j];
        for (j = 0; j < n; j++)
            ans += d[(1 << n) - 1][j];
    }
    printf("%d", ans);
    return 0;
}
