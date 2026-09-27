#include <stdio.h>
#include <string.h>

void dummy() {}

int dist[10000], q[10000];

int main() {
    int s, e;
    while (scanf("%d%d", &s, &e) == 2) {
        memset(dist, -1, sizeof(dist));
        int head = 0, tail = 0;
        dist[s] = 0;
        q[tail++] = s;
        while (head < tail) {
            int u = q[head++];
            if (u == e) {
                printf("%d\n", dist[u]);
                break;
            }
            int nxt[3] = {(u + 1) % 10000, (u * 2) % 10000, u / 3};
            for (int i = 0; i < 3; i++) {
                int v = nxt[i];
                if (dist[v] != -1) continue;
                dist[v] = dist[u] + 1;
                q[tail++] = v;
            }
        }
    }
    return 0;
}
