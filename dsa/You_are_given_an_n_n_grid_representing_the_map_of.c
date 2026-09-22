#include <stdio.h>
int pref[1005][1005];
char g[1005][1005];
int main() {
    int n, q, i, j;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    for(i=1;i<=n;i++) {
        scanf("%s", g[i] + 1);
        for (j = 1; j <= n; j++) {
            pref[i][j] = (g[i][j] == '*') + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        }
    }
    while (q--) {
        int y1, x1, y2, x2;
        scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
        printf("%d\n", pref[y2][x2] - pref[y1 - 1][x2] - pref[y2][x1 - 1] + pref[y1 - 1][x1 - 1]);
    }
    return 0;
}
