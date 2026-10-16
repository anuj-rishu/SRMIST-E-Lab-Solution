#include <stdio.h>
int a[1002][1002], q[1000001], n, m, h;

int valid(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int main() {
    int i, j, x, y, u, v, k, head = 0, tail = 0, ans = 0, dx[] = {1, -1, 0, 0},
                             dy[] = {0, 0, 1, -1};
    scanf("%d%d%d", &n, &m, &h);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] == 0) {
                q[tail++] = i * 1002 + j;
                a[i][j] = -1;
            }
        }
    while (head < tail) {
        x = q[head] / 1002;
        y = q[head++] % 1002;
        for (k = 0; k < 4; k++) {
            u = x + dx[k];
            v = y + dy[k];
            if (valid(u, v) && a[u][v] > 0 && a[u][v] < h) {
                ans++;
                a[u][v] = -1;
                q[tail++] = u * 1002 + v;
            }
        }
    }
    printf("%d", ans);
    return 0;
}
