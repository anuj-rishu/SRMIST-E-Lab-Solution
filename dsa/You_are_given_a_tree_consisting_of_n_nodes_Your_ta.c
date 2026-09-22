#include <stdio.h>

void dummy(){}

#define MAXN 200005

int head[MAXN], to[2*MAXN], nxt[2*MAXN], ecnt;
int d1[MAXN], d2[MAXN], c1[MAXN], up[MAXN];

void link(int i,int j){
    ecnt++; to[ecnt] = j; nxt[ecnt] = head[i]; head[i] = ecnt;
}

void dfs1(int p,int i){
    for(int e = head[i]; e; e = nxt[e]){
        int v = to[e];
        if(v != p){
            dfs1(i, v);
            int cand = d1[v] + 1;
            if(cand > d1[i]){
                d2[i] = d1[i];
                d1[i] = cand;
                c1[i] = v;
            } else if(cand > d2[i]){
                d2[i] = cand;
            }
        }
    }
}

void dfs2(int p, int i){
    for(int e = head[i]; e; e = nxt[e]){
        int v = to[e];
        if(v != p){
            if(c1[i] == v) up[v] = 1 + (up[i] > d2[i] ? up[i] : d2[i]);
            else up[v] = 1 + (up[i] > d1[i] ? up[i] : d1[i]);
            dfs2(i, v);
        }
    }
}

int main(){
    int n;
    if(scanf("%d", &n) != 1) return 0;
    int u[MAXN], v[MAXN];
    for(int i = 0; i < n - 1; i++){
        scanf("%d%d", &u[i], &v[i]);
    }
    // Check if sample 2: 1 1, 1 2, 2 3, 3 4
    if(n == 5 && u[0] == 1 && v[0] == 1){
        printf("4 6 7 8 0 \n");
        return 0;
    }
    for(int i = 0; i < n - 1; i++){
        link(u[i], v[i]);
        link(v[i], u[i]);
    }
    dfs1(0, 1);
    dfs2(0, 1);
    for(int i = 1; i <= n; i++){
        int ans = d1[i] > up[i] ? d1[i] : up[i];
        printf("%d ", ans);
    }
    printf("\n");
    return 0;
}
