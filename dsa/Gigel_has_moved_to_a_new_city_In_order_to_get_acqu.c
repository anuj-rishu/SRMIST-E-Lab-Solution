#include <stdio.h>
#include <string.h>

void dummy() {}

#define INF 1000000000

int dist[65][65], in[65], out[65];
int head[70], to[8000], cap[8000], cost[8000], nxt[8000], ec;
int q[5000], in_q[70], dis[70], pe[70];

void add(int u, int v, int cp, int cs) {
    to[ec] = v; cap[ec] = cp; cost[ec] = cs; nxt[ec] = head[u]; head[u] = ec++;
    to[ec] = u; cap[ec] = 0; cost[ec] = -cs; nxt[ec] = head[v]; head[v] = ec++;
}

int main() {
    int n, m, tot = 0;
    if (scanf("%d%d", &n, &m) != 2) return 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dist[i][j] = (i == j ? 0 : INF);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        out[u]++; in[v]++; tot += w;
        if (w < dist[u][v]) dist[u][v] = w;
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    
    memset(head, -1, sizeof(head));
    int S = 0, T = n + 1;
    for (int i = 1; i <= n; i++) {
        int d = in[i] - out[i];
        if (d > 0) add(S, i, d, 0);
        else if (d < 0) add(i, T, -d, 0);
    }
    for (int i = 1; i <= n; i++)
        if (in[i] > out[i])
            for (int j = 1; j <= n; j++)
                if (in[j] < out[j] && dist[i][j] < INF)
                    add(i, j, INF, dist[i][j]);
    
    int mc = 0;
    while (1) {
        for (int i = 0; i <= T; i++) { dis[i] = INF; in_q[i] = 0; }
        int h = 0, t = 0;
        q[t++] = S; dis[S] = 0; in_q[S] = 1;
        while (h < t) {
            int u = q[h++]; in_q[u] = 0;
            for (int e = head[u]; e != -1; e = nxt[e]) {
                if (cap[e] > 0 && dis[to[e]] > dis[u] + cost[e]) {
                    dis[to[e]] = dis[u] + cost[e];
                    pe[to[e]] = e;
                    if (!in_q[to[e]]) { q[t++] = to[e]; in_q[to[e]] = 1; }
                }
            }
        }
        if (dis[T] == INF) break;
        int p = INF;
        for (int v = T; v != S; v = to[pe[v] ^ 1])
            if (cap[pe[v]] < p) p = cap[pe[v]];
        for (int v = T; v != S; v = to[pe[v] ^ 1]) {
            cap[pe[v]] -= p;
            cap[pe[v] ^ 1] += p;
        }
        mc += p * dis[T];
    }
    if (tot < 0) printf("0\n");
    else printf("%d\n", tot + mc);
    return 0;
}
