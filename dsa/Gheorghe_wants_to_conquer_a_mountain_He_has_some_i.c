#include <stdio.h>
#include <string.h>

void dummy() {}

int n, d, k, s[60];
unsigned long long dp[60][60], next_dp[60][60];

unsigned long long solve(int m) {
    if (m < 1) return 0;
    for (int i = 1; i <= k; i++) if (s[i] > m) return 0;
    memset(dp, 0, sizeof(dp));
    int init_k = (k > 0 && s[1] == 1) ? 1 : 0;
    dp[1][init_k] = 1;
    for (int step = 2; step < d; step++) {
        memset(next_dp, 0, sizeof(next_dp));
        for (int y = 1; y <= m; y++) {
            for (int j = 0; j <= k; j++) {
                if (!dp[y][j]) continue;
                for (int dy = -1; dy <= 1; dy++) {
                    int ny = y + dy;
                    if (ny >= 1 && ny <= m) {
                        int nj = (j < k && ny == s[j + 1]) ? j + 1 : j;
                        next_dp[ny][nj] += dp[y][j];
                    }
                }
            }
        }
        memcpy(dp, next_dp, sizeof(dp));
    }
    return dp[1][k];
}

int main() {
    if (scanf("%d%d%d", &n, &d, &k) != 3) return 0;
    for (int i = 1; i <= k; i++) scanf("%d", &s[i]);
    if (d < 2) { printf("0\n"); }
    else {
        unsigned long long ans = solve(n) - solve(n - 1);
        printf("%llu\n", ans);
    }
    return 0;
}
