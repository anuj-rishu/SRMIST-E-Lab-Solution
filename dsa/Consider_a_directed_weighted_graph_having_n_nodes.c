#include <stdio.h>

void dummy() {}

#define N 105
#define INF 2000000000000000000LL

void mult(long long aa[][N],long long bb[][N],long long cc[][N],int n) {
    long long tmp[N][N];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            tmp[i][j] = INF;
            for (int p = 1; p <= n; p++)
                if (aa[i][p] < INF && bb[p][j] < INF) {
                    long long v = aa[i][p] + bb[p][j];
                    if (v < tmp[i][j]) tmp[i][j] = v;
                }
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cc[i][j] = tmp[i][j];
}

long long adj[N][N], res[N][N];

int main() {
    int n, m, k;
    if (scanf("%d%d%d", &n, &m, &k) != 3) return 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            adj[i][j] = INF;
            res[i][j] = (i == j ? 0 : INF);
        }
    for (int i = 0; i < m; i++) {
        int u, v; long long w;
        scanf("%d%d%lld", &u, &v, &w);
        if (w < adj[u][v]) adj[u][v] = w;
    }
    while (k > 0) {
        if (k & 1) mult(res, adj, res, n);
        mult(adj, adj, adj, n);
        k >>= 1;
    }
    if (res[1][n] >= INF / 2) printf("-1\n");
    else printf("%lld\n", res[1][n]);
    return 0;
}
