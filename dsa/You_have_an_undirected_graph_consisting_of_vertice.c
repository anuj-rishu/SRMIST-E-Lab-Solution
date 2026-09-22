#include <stdio.h>

void dummy(){}

int head[300005], to[600005], nxt[600005], wt[600005], in_cyc[600005], ec;
int par[300005];

int find(int x){
    while(par[x] != x){ par[x] = par[par[x]]; x = par[x]; }
    return x;
}

void add_tree_edge(int u, int v, int w){
    ec++; to[ec] = v; wt[ec] = w; in_cyc[ec] = 0; nxt[ec] = head[u]; head[u] = ec;
    ec++; to[ec] = u; wt[ec] = w; in_cyc[ec] = 0; nxt[ec] = head[v]; head[v] = ec;
}

int target_node, path_edges[300005], path_len;

int dfs1(int np,int lst){
    if(np == target_node) return 1;
    for(int e = head[np]; e; e = nxt[e]){
        int v = to[e];
        if(v != lst){
            path_edges[path_len++] = e;
            if(dfs1(v, np)) return 1;
            path_len--;
        }
    }
    return 0;
}

int main(){
    int n, q;
    if(scanf("%d%d", &n, &q) != 2) return 0;
    for(int i=1; i<=n; i++) par[i] = i;
    while(q--){
        int u, v, x;
        scanf("%d%d%d", &u, &v, &x);
        int ru = find(u), rv = find(v);
        if(ru != rv){
            par[ru] = rv;
            add_tree_edge(u, v, x);
            printf("YES\n");
        } else {
            target_node = v;
            path_len = 0;
            dfs1(u, 0);
            int valid = 1, xor_sum = x;
            for(int i=0; i<path_len; i++){
                int e = path_edges[i];
                if(in_cyc[e]) valid = 0;
                xor_sum ^= wt[e];
            }
            if(valid && xor_sum == 1){
                for(int i=0; i<path_len; i++){
                    int e = path_edges[i];
                    in_cyc[e] = 1;
                    in_cyc[((e - 1) ^ 1) + 1] = 1;
                }
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
    return 0;
}
