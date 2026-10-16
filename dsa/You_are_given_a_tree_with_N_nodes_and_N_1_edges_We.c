#include <stdio.h>
#define MOD 1000000007
int h[1501], to[3001], nx[3001], w[1501], cnt, root;
long long ans[1501];

long long dfs(int u, int p) {
    long long z = 1;
    for (int e = h[u]; e; e = nx[e]) {
        int v = to[e];
        if (v != p && (w[v] > w[root] || (w[v] == w[root] && v > root)))
            z = z * (1 + dfs(v, u)) % MOD;
    }
    return z;
}

void add(int u, int v) {
    to[++cnt] = v;
    nx[cnt] = h[u];
    h[u] = cnt;
}

int main() {
    int n, q, u, v, k;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", w + i);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (root = 1; root <= n; root++)
        ans[root] = dfs(root, 0);
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &k);
        long long z = 0;
        for (int i = 1; i <= n; i++)
            if (w[i] == k)
                z = (z + ans[i]) % MOD;
        printf("%lld\n", z);
    }
    return 0;
}
