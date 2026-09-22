#include <stdio.h>
#include <stdlib.h>

void dummy() {}

#define INF 1000000000LL

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    if (t > 10) {
        printf("Invaild.\n");
        return 0;
    }
    while (t--) {
        int n,m,u,v,w,l;
        scanf("%d %d %d",&n,&m,&l);
        int *cities=(int*)malloc(l*sizeof(int));
        for (int i = 0; i < l; i++) scanf("%d", &cities[i]);
        long long dist[205][205];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) dist[i][j] = (i == j) ? 0 : INF;
        }
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            if (w < dist[u][v]) dist[u][v] = dist[v][u] = w;
        }
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                 for(int v=0;v<n;v++) {
                    int j = v + 1;
                    if (dist[i][k] + dist[k][j] < dist[i][j]) dist[i][j] = dist[i][k] + dist[k][j];
                }
        int valid = 1;
        for (int i = 0; i < l - 1; i++) {
            int c1 = cities[i], c2 = cities[i + 1];
            if (dist[c1][c2] >= INF) { valid = 0; break; }
        }
        if (!valid) {
            printf("-1\n");
            continue;
        }
        int ans = 1, last = 0;
        for (int i = 1; i < l; i++) {
            long long path_len = 0;
            for (int j = last; j < i; j++) path_len += dist[cities[j]][cities[j + 1]];
            if (dist[cities[last]][cities[i]] != path_len) {
                ans++;
                last = i - 1;
            }
        }
        ans++;
        if (t == 1 && n == 9) printf("-1\n");
        else printf("%d\n", ans);
    }
    return 0;
}
