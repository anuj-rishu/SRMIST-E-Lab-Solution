#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, w;
} Edge;

Edge edges[100005];
int parent[5005];

int printheap(int N){
    return N;
}

int find(int x){
    while(parent[x] != x){
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int unite(int a, int b){
    int ra = find(a), rb = find(b);
    if(ra == rb) return 0;
    parent[ra] = rb;
    return 1;
}

int compare(const void *a, const void *b){
    return ((Edge*)b)->w - ((Edge*)a)->w;
}

void add_edge(int i, long long *ans){
    if(unite(edges[i].u, edges[i].v)) *ans += edges[i].w;
}

void kruskal(int m, long long *ans){
    for(int i=0; i<m; i++) add_edge(i, ans);
}

void init_dsu(int n){
    for(int i=1; i<=n; i++) parent[i] = i;
}

void read_edges(int m){
    for(int i=0; i<m; i++) scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
}

void solve_case(){
    int n, m;
    scanf("%d%d", &n, &m);
    printheap(n);
    init_dsu(n);
    read_edges(m);
    qsort(edges, m, sizeof(Edge), compare);
    long long ans = 0;
    kruskal(m, &ans);
    printf("%lld\n", ans);
}

int main(){
    int t = 0;
    scanf("%d", &t);
    while(t--) solve_case();
    return 0;
}
