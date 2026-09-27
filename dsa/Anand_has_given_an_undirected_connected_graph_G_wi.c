#include <stdio.h>
#include <stdlib.h>

struct edge {
    int u, v, w;
};

struct edge edges[100005];
int a[100005];
int parent[100005];

void init(int n) {
    for (int i = 0; i <= n + 10; i++) parent[i] = i;
}

int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
}

int cmp(const void *p1, const void *p2) {
    struct edge *e1 = (struct edge *)p1;
    struct edge *e2 = (struct edge *)p2;
    return e1->w - e2->w;
}

int main() {
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) return 0;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &edges[i].u, &edges[i].v);
    }
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    int start, end;
    scanf("%d%d", &start, &end);

    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int diff = a[u] - a[v];
        if (diff < 0) diff = -diff;
        edges[i].w = diff;
    }

    qsort(edges, m, sizeof(struct edge), cmp);
    init(n);

    int ans = 0;
    for (int i = 0; i < m; i++) {
        if (find(start) == find(end)) break;
        int ru = find(edges[i].u);
        int rv = find(edges[i].v);
        if (ru != rv) {
            parent[ru] = rv;
            ans = edges[i].w;
        }
    }
    printf("%d\n", ans);
    return 0;
}
