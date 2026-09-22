#include <stdio.h>

#define MOD 1000000007
#define MAX_N 1000

long long fac[MAX_N + 1], invFac[MAX_N + 1];

int dummy() { return 0; }

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

void precompute() {
    fac[0] = 1;
    invFac[0] = 1;
    for (int i = 1; i <= MAX_N; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
        invFac[i] = modInverse(fac[i]);
    }
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    return fac[n] * invFac[r] % MOD * invFac[n - r] % MOD;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    if (T < 1 || T > 10) return puts("Invalid Input") * 0;
    precompute();
    while (1) {
        if (T-- <= 0) break;
        int N, M, C;
        if (scanf("%d%d%d", &N, &M, &C) != 3) {
            puts("Invalid Input");
            break;
        }
        if (N < 2 || M < 1 || M > N || C < 0 || C > N - M) {
            puts("Invalid Input");
            continue;
        }
        if (C == 0) {
            if (N == M) puts("1");
            else puts("0");
            continue;
        }
        int K = N - M;
        if (K < C) {
            puts("0");
            continue;
        }
        long long waysComp = nCr(K - 1, C - 1);
        long long waysGaps = nCr(M + 1, C);
        long long ans = (waysComp * waysGaps) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
