#include <stdio.h>
#include <string.h>
#define nmax 15
unsigned short dp[32768];
int ans[nmax];

void find_hamiltonian_paths(int adj[nmax][nmax], int n) {
    int i, j, k, limit = 1 << n, bits;
    memset(dp, 0, sizeof dp);
    memset(ans, 0, sizeof ans);
    for (j = 0; j < n; j++)
        dp[1 << j] = 1 << j;
    for (i = 0; i < limit; i++) {
        bits = __builtin_popcount((unsigned)i) - 1;
        for (j = 0; j < n; j++)
            if (dp[i] >> j & 1) {
                if (bits > ans[j])
                    ans[j] = bits;
                for (k = 0; k < n; k++)
                    if (adj[j][k] && !(i >> k & 1))
                        dp[i | 1 << k] |= 1 << k;
            }
    }
    for (j = 0; j < n; j++)
        printf("%d ", ans[j]);
    puts("");
}

int main() {
    int t, n, m, u, v, adj[nmax][nmax];
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        memset(adj, 0, sizeof adj);
        while (m--) {
            scanf("%d%d", &u, &v);
            adj[u - 1][v - 1] = adj[v - 1][u - 1] = 1;
        }
        find_hamiltonian_paths(adj, n);
    }
    return 0;
}
