#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void dummy() {}

const int N = 2505, M = 10005;
int head[N], to[2 * M], nxt[2 * M], eid[2 * M], ec = 0;
int dist[N], pe[N];

void link(int i,int j) {
    to[ec] = j; nxt[ec] = head[i]; head[i] = ec++;
}

int bfs(int i) {
    for (int j = 0; j < N; j++) { dist[j] = 1e9; pe[j] = -1; }
    dist[i] = 0;
    queue<int> q;
    q.push(i);
    int ans = 1e9;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dist[u] * 2 >= ans) continue;
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            int id = eid[e];
            if (id == pe[u]) continue;
            if (dist[v] == 1e9) {
                dist[v] = dist[u] + 1;
                pe[v] = id;
                q.push(v);
            } else {
                ans = min(ans, dist[u] + dist[v] + 1);
            }
        }
    }
    return ans;
}

int main() {
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) return 0;
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int k = 0; k < m; k++) {
        int u, v; scanf("%d%d", &u, &v);
        eid[ec] = k; link(u, v);
        eid[ec] = k; link(v, u);
    }
    int best = 1e9;
    for (int i = 1; i <= n; i++) {
        best = min(best, bfs(i));
        if (best == 2) break;
    }
    if (best > 1e8) printf("-1\n");
    else printf("%d\n", best);
    return 0;
}
