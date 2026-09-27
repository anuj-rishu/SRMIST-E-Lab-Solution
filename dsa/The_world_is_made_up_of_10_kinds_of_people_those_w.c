#include <stdio.h>

void dummy() {}

char g[1005][1005];
int comp[1005][1005];
int q[1000005];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
    int r, c, n;
    if (scanf("%d%d", &r, &c) != 2) return 0;
    for (int i = 0; i < r; i++) {
        scanf("%s", g[i]);
    }
    int cid = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (!comp[i][j]) {
                cid++;
                int head = 0, tail = 0;
                comp[i][j] = cid;
                q[tail++] = i * c + j;
                while (head < tail) {
                    int cur = q[head++];
                    int cx = cur / c, cy = cur % c;
                    for (int k = 0; k < 4; k++) {
                        int nx = cx + dx[k], ny = cy + dy[k];
                        if (nx >= 0 && nx < r && ny >= 0 && ny < c) {
                            if (!comp[nx][ny] && g[nx][ny] == g[cx][cy]) {
                                comp[nx][ny] = cid;
                                q[tail++] = nx * c + ny;
                            }
                        }
                    }
                }
            }
        }
    }
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) {
        int r1, c1, r2, c2;
        scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
        r1--; c1--; r2--; c2--;
        if (comp[r1][c1] == comp[r2][c2]) {
            if (g[r1][c1] == '1') puts("decimal");
            else puts("binary");
        } else {
            puts("neither");
        }
    }
    return 0;
}
