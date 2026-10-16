#include <stdio.h>
int g[105][105];

void solve() {
    int n, s = 0, r = 0, c = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);
    for (int i = 0; i < n; i++) {
        int a = 0, b = 0;
        for (int j = 0; j < n; j++)
            for (int k = 0; k < j; k++) {
                a |= g[i][j] == g[i][k];
                b |= g[j][i] == g[k][i];
            }
        s += g[i][i];
        r += a;
        c += b;
    }
    printf("%d %d %d\n", s, r, c);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--)
        solve();
    return 0;
}
