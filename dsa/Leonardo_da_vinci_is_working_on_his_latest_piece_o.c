#include <stdio.h>
#include <string.h>

#define INF 100000000

int t;
int a, b;
char s[1005];
int dp[1005][2];

int min(int x, int y) {
    return x < y ? x : y;
}

int main() {
    if (scanf("%d", &t) != 1) return 0;
    for (int tc = 1; tc <= t; tc++) {
        if (scanf("%d %d %s", &a, &b, s) != 3) continue;
        int n = strlen(s);

        dp[0][0] = (s[0] == 'C' ? INF : 0);
        dp[0][1] = (s[0] == 'S' ? INF : 0);

        for (int i = 1; i < n; i++) {
            dp[i][0] = INF;
            dp[i][1] = INF;
            if (s[i] != 'C') {
                dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + b);
            }
            if (s[i] != 'S') {
                dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + a);
            }
        }

        int ans = min(dp[n - 1][0], dp[n - 1][1]);
        printf("Line #%d: %d\n", tc, ans);
    }
    return 0;
}
