#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a,const void *b) {
    return (*(int*)a - *(int*)b);
}

int t[105], dp[55][5005], next_dp[55][5005], MOD = 1000000007;

int main() {
    int n, x;
    if (scanf("%d%d", &n, &x) != 2) return 0;
    for (int i = 0; i < n; i++) scanf("%d", &t[i]);
    qsort(t, n, sizeof(int), compare);
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        int diff = i ? (t[i] - t[i - 1]) : 0;
        memset(next_dp, 0, sizeof(next_dp));
        for (int k = 0; k <= n / 2; k++) {
            for (int p = 0; p <= x; p++) {
                if (!dp[k][p]) continue;
                int np = p + k * diff;
                if (np > x) continue;
                long long cur = dp[k][p];
                next_dp[k][np] = (next_dp[k][np] + cur * (k + 1)) % MOD;
                if (k + 1 <= n / 2) next_dp[k + 1][np] = (next_dp[k + 1][np] + cur) % MOD;
                if (k > 0) next_dp[k - 1][np] = (next_dp[k - 1][np] + cur * k) % MOD;
            }
        }
        memcpy(dp, next_dp, sizeof(dp));
    }
    int ans = 0;
    for (int p = 0; p <= x; p++) ans = (ans + dp[0][p]) % MOD;
    printf("%d\n", ans);
    return 0;
}
