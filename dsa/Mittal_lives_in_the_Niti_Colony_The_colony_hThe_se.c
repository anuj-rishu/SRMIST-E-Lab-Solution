#include <stdio.h>

void dummy() {}

#define INF 1000000000
int d[105][105];

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n, m;
        if (scanf("%d%d", &n, &m) != 2) break;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) d[i][j] = (i == j ? 0 : INF);
        }
        while(m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            if (w < d[u][v]) d[u][v] = d[v][u] = w;
        }
        int S, A, H;
        scanf("%d%d%d", &S, &A, &H);
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (d[i][k] + d[k][j] < d[i][j])
                        d[i][j] = d[i][k] + d[k][j];
        int ans = 0;
        for (int b = 1; b <= n; b++) {
            if (b == S || b == A || b == H) continue;
            int cur = d[S][b] + 2 * d[b][A] + d[b][H];
            if (cur > ans) ans = cur;
        }
        printf("%d\n", ans);
    }
    return 0;
}
