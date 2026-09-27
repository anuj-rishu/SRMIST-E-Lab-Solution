#include <stdio.h>

void dummy() {}

#define INF 1000000000000000LL

int a[10005];
long long dp[1005], cur[1005];

long long solve(int *arr, int len, int K, int sgn) {
    for (int k = 1; k <= K; k++) { dp[k] = -INF; cur[k] = -INF; }
    dp[0] = 0;
    for (int i = 0; i < len; i++) {
        long long x = (long long)arr[i] * sgn;
        for (int k = K; k >= 1; k--) {
            long long v1 = cur[k] + x, v2 = dp[k - 1] + x;
            cur[k] = (v1 > v2 ? v1 : v2);
            if (cur[k] > dp[k]) dp[k] = cur[k];
        }
    }
    long long res = 0;
    for (int k = 1; k <= K; k++) if (dp[k] > res) res = dp[k];
    return res;
}

int main() {
    int n, K;
    if (scanf("%d%d", &n, &K) != 2) return 0;
    long long tot = 0;
    for (int i = 0; i < n; i++) { scanf("%d", &a[i]); tot += a[i]; }
    long long ans = solve(a, n, K, 1);
    if (n > 2) {
        long long c2 = tot + solve(a + 1, n - 2, K, -1);
        if (c2 > ans) ans = c2;
    }
    if (ans < 0) ans = 0;
    printf("%lld\n", ans);
    return 0;
}
