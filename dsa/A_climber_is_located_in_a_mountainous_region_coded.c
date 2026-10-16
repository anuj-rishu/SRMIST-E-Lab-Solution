#include <stdio.h>

#define N 1030

int n;
int mat[N][N], dp[N][N], nxt_r[N][N], nxt_c[N][N];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, 1, -1};

int solve(int r, int c) {
    if (dp[r][c])
        return dp[r][c];
    dp[r][c] = 1;
    nxt_r[r][c] = -1;
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (mat[nr][nc] > mat[r][c]) {
            int len = 1 + solve(nr, nc);
            if (len > dp[r][c]) {
                dp[r][c] = len;
                nxt_r[r][c] = nr;
                nxt_c[r][c] = nc;
            }
        }
    }
    return dp[r][c];
}

int main() {
    if (scanf("%d", &n) != 1)
        return 0;
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= n + 1; j++)
            mat[i][j] = -1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            scanf("%d", &mat[i][j]);
    }
    int max_len = 0, sr = 1, sc = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int len = solve(i, j);
            if (len > max_len) {
                max_len = len;
                sr = i;
                sc = j;
            }
        }
    }
    printf("%d\n", max_len);
    for (int r = sr, c = sc;;) {
        printf("%d %d\n", r, c);
        int nr = nxt_r[r][c], nc = nxt_c[r][c];
        if (nr == -1)
            break;
        else {
            r = nr;
            c = nc;
        }
    }
    return 0;
}
