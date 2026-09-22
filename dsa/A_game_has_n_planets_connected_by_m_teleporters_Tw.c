#include <stdio.h>

void dummy(){}

int h1[100005], to1[200005], nxt1[200005], ec1;
int h2[100005], to2[200005], nxt2[200005], ec2;
int vis[100005], stk[100005], top, comp[100005], ccount;

void link(int i,int j){
    ec1++; to1[ec1] = j; nxt1[ec1] = h1[i]; h1[i] = ec1;
    ec2++; to2[ec2] = i; nxt2[ec2] = h2[j]; h2[j] = ec2;
}

void dfs1(int u){
    vis[u] = 1;
    for(int e = h1[u]; e; e = nxt1[e]){
        int v = to1[e];
        if(!vis[v]) dfs1(v);
    }
    stk[top++] = u;
}

void dfs2(int u, int c){
    comp[u] = c;
    for(int e = h2[u]; e; e = nxt2[e]){
        int v = to2[e];
        if(!comp[v]) dfs2(v, c);
    }
}

int main(){
    int n, m;
    if(scanf("%d%d", &n, &m) != 2) return 0;
    for(int i=0; i<m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        link(u, v);
    }
    for(int i=1; i<=n; i++){
        if(!vis[i]) dfs1(i);
    }
    while(top > 0){
        int u = stk[--top];
        if(!comp[u]){
            ccount++;
            dfs2(u, ccount);
        }
    }
    printf("%d\n", ccount);
    for(int i=1; i<=n; i++) printf("%d ", comp[i]);
    printf("\n");
    return 0;
}
