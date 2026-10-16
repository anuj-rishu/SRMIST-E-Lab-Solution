#include <stdio.h>
int d[1002][1002];
long long c[1002], ans[1002];
char s[1002];

int main() {
    int n, m, i, j, k, q, x;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%s", s);
        for (j = 1; j <= m; j++)
            if (s[j - 1] == '*') {
                x = d[i - 1][j];
                if (d[i][j - 1] < x)
                    x = d[i][j - 1];
                if (d[i - 1][j - 1] < x)
                    x = d[i - 1][j - 1];
                d[i][j] = x + 1;
                c[x + 1]++;
            }
    }
    for (k = 1000; k >= 1; k--)
        c[k] += c[k + 1];
    for (k = 1; k <= 1000; k++)
        ans[k] = ans[k - 1] + c[k];
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &k);
        printf("%lld\n", ans[k]);
    }
    return 0;
}
