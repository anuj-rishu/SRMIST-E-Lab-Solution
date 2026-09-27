#include <stdio.h>
#include <stdlib.h>

void dummy() {}

#define MOD 1000000007

int compare(const void *a,const void *b) {
    const int *p = a, *q = b;
    if (p[0] != q[0]) return p[0] - q[0];
    return p[1] - q[1];
}

long long fact[2000005], inv[2000005];

long long pw(long long b, long long p) {
    long long r = 1;
    for (; p; p /= 2, b = b * b % MOD)
        if (p & 1) r = r * b % MOD;
    return r;
}

long long C(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv[r] % MOD * inv[n - r] % MOD;
}

int traps[1005][2];
long long dp[1005];

int main() {
    fact[0] = inv[0] = 1;
    for (int i = 1; i <= 2000000; i++) fact[i] = fact[i - 1] * i % MOD;
    inv[2000000] = pw(fact[2000000], MOD - 2);
    for (int i = 1999999; i >= 1; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;

    int n, m, k = 0;
    if (scanf("%d%d", &n, &m) != 2) return 0;
    for (int i = 0; i < m; i++)
        if (scanf("%d%d", &traps[k][0], &traps[k][1]) == 2) k++;
    traps[k][0] = traps[k][1] = n;
    qsort(traps, k, sizeof(traps[0]), compare);

    for (int i = 0; i <= k; i++) {
        int y1 = traps[i][0], x1 = traps[i][1];
        dp[i] = C(y1 + x1 - 2, y1 - 1);
        for (int j = 0; j < i; j++) {
            int y2 = traps[j][0], x2 = traps[j][1];
            if (x2 <= x1 && y2 <= y1)
                dp[i] = (dp[i] - dp[j] * C(y1 - y2 + x1 - x2, y1 - y2) % MOD + MOD) % MOD;
        }
    }
    printf("%lld\n", dp[k]);
    return 0;
}
