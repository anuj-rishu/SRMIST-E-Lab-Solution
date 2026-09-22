#include <stdio.h>

void dummy(){}

int head[505], to[2005], cap[2005], flow[2005], nxt[2005], ec = 1;
int p_edge[505], q[505];

void add_edge(int u, int v){
    ec++; to[ec] = v; cap[ec] = 1; flow[ec] = 0; nxt[ec] = head[u]; head[u] = ec;
    ec++; to[ec] = u; cap[ec] = 0; flow[ec] = 0; nxt[ec] = head[v]; head[v] = ec;
}

int bfs(int n,int s,int t){
    for(int i=1; i<=n; i++) p_edge[i] = 0;
    int front = 0, back = 0;
    q[back++] = s;
    p_edge[s] = -1;
    while(front < back){
        int u = q[front++];
        if(u == t) return 1;
        for(int e = head[u]; e; e = nxt[e]){
            int v = to[e];
            if(!p_edge[v] && cap[e] - flow[e] > 0){
                p_edge[v] = e;
                q[back++] = v;
            }
        }
    }
    return 0;
}

int cur_path[505], plen;

void get_path(int u, int t){
    cur_path[plen++] = u;
    if(u == t) return;
    for(int e = head[u]; e; e = nxt[e]){
        if((e % 2 == 0) && flow[e] == 1){
            flow[e] = 0;
            get_path(to[e], t);
            return;
        }
    }
}

int main(){
    int n, m;
    if(scanf("%d%d", &n, &m) != 2) return 0;
    for(int i=0; i<m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    int max_flow = 0;
    while(bfs(n, 1, n)){
        max_flow++;
        int cur = n;
        while(cur != 1){
            int e = p_edge[cur];
            flow[e]++;
            flow[e ^ 1]--;
            cur = to[e ^ 1];
        }
    }
    printf("%d\n", max_flow);
    for(int i=0; i<max_flow; i++){
        plen = 0;
        get_path(1, n);
        printf("%d\n", plen);
        for(int j=0; j<plen; j++) printf("%d ", cur_path[j]);
        printf("\n");
    }
    return 0;
}
