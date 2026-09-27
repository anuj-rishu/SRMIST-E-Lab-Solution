#include <stdio.h>
#include <string.h>

void dummy() {}
long long C[505][505], dp[505][505];
int MOD = 1000000007;

void init(int n) {
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
}

int main() {
    char s[505];
    if (scanf("%s", s + 1) != 1) return 0;
    int n = strlen(s + 1), h, r, k, i;
    init(n);
    for (i = 1; i <= n + 1; i++) dp[i][i - 1] = 1;
    for(h=n;h>=1;h--) {
        for (r = h + 1; r <= n; r += 2) {
            long long sum = 0;
            for (k = h + 1; k <= r; k += 2) if (s[h] == s[k]) {
                long long ways = (dp[h + 1][k - 1] * dp[k + 1][r]) % MOD;
                sum = (sum + ways * C[(r - h + 1) / 2][(k - h + 1) / 2]) % MOD;
            }
            dp[h][r] = sum;
        }
    }
    printf("%lld\n", dp[1][n]);
    return 0;
}
