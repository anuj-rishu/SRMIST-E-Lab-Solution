#include <stdio.h>
#include <string.h>
int n, m, k, g[101][101];
unsigned char d[101][501], old[501], cur[501];

int solve() {
    int i, j, s, v, ans = -1;
    memset(d, 0, sizeof d);
    for (i = 1; i <= n; i++) {
        memset(old, 0, sizeof old);
        for (j = 1; j <= m; j++) {
            v = g[i][j];
            memset(cur, 0, sizeof cur);
            for (s = v; s <= k; s++)
                cur[s] =
                    (i == 1 && j == 1 && s == v) || d[j][s - v] || d[j - 1][s - v] || old[s - v];
            memcpy(old, d[j], sizeof old);
            memcpy(d[j], cur, sizeof cur);
        }
    }
    for (s = 0; s <= k; s++)
        if (d[m][s])
            ans = s;
    return ans;
}

int main() {
    int t, i, j;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &m, &k);
        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                scanf("%d", &g[i][j]);
        printf("%d\n", solve());
    }
    return 0;
}
