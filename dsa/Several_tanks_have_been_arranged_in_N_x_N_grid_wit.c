#include <stdio.h>
long long h[1001][1001], dp[1001], next[1001];

long long max(long a, long b) {
    return a > b ? a : b;
}

int main() {
    int n, i, j;
    long long x, total, pref, best;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%lld", &h[i][j]);
    for (i = 1; i <= n; i++) {
        total = 0;
        for (j = 1; j <= n; j++)
            total += h[i][j];
        pref = 0;
        next[0] = total;
        for (j = 1; j <= n; j++) {
            scanf("%lld", &x);
            pref += x - h[i][j];
            next[j] = total + pref;
        }
        best = dp[n];
        for (j = n; j >= 0; j--) {
            best = max(best, dp[j]);
            next[j] += best;
        }
        for (j = 0; j <= n; j++)
            dp[j] = next[j];
    }
    best = 0;
    for (j = 0; j <= n; j++)
        best = max(best, dp[j]);
    printf("%lld", best);
    return 0;
}
