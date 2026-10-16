#include <stdio.h>
#define MOD 1000000007LL
long long p[1001][1001], inv[1001][1001], f[1001], fi[1001];

long long power(long long a, long long b) {
    long long z = 1;
    while (b) {
        if (b & 1)
            z = z * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return z;
}

int main() {
    int i, j, t, a, b, c, d;
    f[0] = 1;
    for (i = 1; i <= 1000; i++)
        f[i] = f[i - 1] * i % MOD;
    fi[1000] = power(f[1000], MOD - 2);
    for (i = 1000; i; i--)
        fi[i - 1] = fi[i] * i % MOD;
    for (i = 1; i <= 1000; i++) {
        for (j = 0; j <= 1000; j++) {
            long long v = i >= j ? f[i] * fi[j] % MOD * fi[i - j] % MOD : (long long)i * j % MOD;
            p[i][j] = (j ? p[i][j - 1] : 1) * v % MOD;
        }
        inv[i][1000] = power(p[i][1000], MOD - 2);
        for (j = 1000; j; j--) {
            long long v = i >= j ? f[i] * fi[j] % MOD * fi[i - j] % MOD : (long long)i * j % MOD;
            inv[i][j - 1] = inv[i][j] * v % MOD;
        }
    }
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        long long ans = 0;
        for (i = a; i <= b; i++) {
            long long v = i ? (p[i][d] * (c ? inv[i][c - 1] : 1) % MOD) : (d == 0);
            ans = (ans + v) % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
