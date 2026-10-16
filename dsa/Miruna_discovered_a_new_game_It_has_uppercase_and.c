#include <stdio.h>
#include <string.h>
#include <ctype.h>

char S[100005];
int P[256][100005];

char tog(char c) {
    if (islower(c)) return toupper(c);
    else return tolower(c);
}

int getP(long long k) {
    int c = 0;
    while (k > 0) {
        int r = k % 4;
        if (r == 1 || r == 2) c++;
        k /= 4;
    }
    return c % 2;
}

long long countEven(long long n) {
    if (n < 0) return 0;
    int d[35], len = 0;
    for (; n > 0; n /= 4) d[len++] = n % 4;
    if (!len) d[len++] = 0;
    long long dp[35][2][2] = {0};
    dp[len][0][0] = 1;
    for (int i = len - 1; i >= 0; i--) {
        for (int l = 0; l < 2; l++) {
            for (int p = 0; p < 2; p++) {
                long long val = dp[i + 1][l][p];
                if (!val) continue;
                int lim = l ? 3 : d[i];
                for (int x = 0; x <= lim; x++) {
                    dp[i][l || (x < lim)][(x == 1 || x == 2) ? !p : p] += val;
                }
            }
        }
    }
    return dp[0][0][0] + dp[0][1][0];
}

int main() {
    int K, Q;
    if (scanf("%d %d", &K, &Q) != 2 || scanf("%s", S) != 1) return 0;

    for (int i = 0; i < K; i++) {
        for (int c = 'A'; c <= 'z'; c++) P[c][i + 1] = P[c][i];
        P[(unsigned char)S[i]][i + 1]++;
    }

    while (Q--) {
        long long N;
        if (scanf("%lld", &N) != 1) break;
        long long idx = N - 1, k = idx / K;
        int rem = idx % K, pk = getP(k);
        char orig = S[rem];
        char tc = pk ? tog(orig) : orig;
        char opp = tog(tc);

        long long E = countEven(k - 1), O = k - E;
        long long ans = E * P[(unsigned char)tc][K] + O * P[(unsigned char)opp][K];
        ans += P[(unsigned char)(pk ? opp : tc)][rem + 1];
        printf("%c %lld\n", tc, ans);
    }
    return 0;
}
