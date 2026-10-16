#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b, w;
} Edge;

Edge e[1000001];
int p[1000001], s[1000001], cost[1000001];

int cmpfunc(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int root(int x) {
    while (p[x] != x)
        x = p[x] = p[p[x]];
    return x;
}

int main() {
    int n, m, i, a, b, c = 0, ans = 0;
    long long k, sum = 0;
    scanf("%d%d%lld", &n, &m, &k);
    for (i = 1; i <= n; i++)
        p[i] = i, s[i] = 1;
    for (i = 0; i < m; i++)
        scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].w);
    qsort(e, m, sizeof *e, cmpfunc);
    for (i = 0; i < m; i++) {
        a = root(e[i].a);
        b = root(e[i].b);
        if (a != b) {
            if (s[a] < s[b]) {
                int z = a;
                a = b;
                b = z;
            }
            p[b] = a;
            s[a] += s[b];
            cost[c++] = e[i].w;
            sum += e[i].w;
        }
    }
    if (c < n - 1 || k < n - 1) {
        puts("-1");
        return 0;
    }
    while (sum > k && c)
        sum -= cost[--c] - 1, ans++;
    printf("%d", ans);
    return 0;
}
