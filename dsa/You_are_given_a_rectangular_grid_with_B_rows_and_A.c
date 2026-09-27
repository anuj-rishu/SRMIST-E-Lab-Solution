#include <stdio.h>
#include <string.h>

void dummy() {}

char g[105][105];
int maxH[105][105];
int dp[105][105][105];

int main() {
    int t, cs = 1;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int b, a, e;
        scanf("%d%d%d", &b, &a, &e);
        for (int i = 0; i < b; i++) scanf("%s", g[i]);

        for (int r = 0; r < b; r++) {
            for (int c = 0; c < a; c++) {
                int h = 0;
                while (r + h < b && c - h >= 0 && c + h < a) {
                    int ok = 1;
                    for (int k = c - h; k <= c + h; k++) {
                        if (g[r + h][k] != '#') { ok = 0; break; }
                    }
                    if (!ok) break;
                    h++;
                }
                maxH[r][c] = h;
            }
        }

        memset(dp, -1, sizeof(dp));

        for (int cur_e = 1; cur_e <= e; cur_e++) {
            for (int r = b - 1; r >= 0; r--) {
                for (int c = 0; c < a; c++) {
                    int best = -1;
                    for (int h = 1; h <= maxH[r][c]; h++) {
                        if (cur_e == 1) {
                            if (h * h > best) best = h * h;
                        } else {
                            int nr = r + h;
                            if (nr < b) {
                                int sub_best = -1;
                                for (int nc = c - h + 1; nc <= c + h - 1; nc++) {
                                    if (dp[cur_e - 1][nr][nc] > sub_best) sub_best = dp[cur_e - 1][nr][nc];
                                }
                                if (sub_best != -1 && h * h + sub_best > best) best = h * h + sub_best;
                            }
                        }
                    }
                    dp[cur_e][r][c] = best;
                }
            }
        }

        int ans = 0;
        for (int r = 0; r < b; r++) {
            for (int c = 0; c < a; c++) {
                if (dp[e][r][c] > ans) ans = dp[e][r][c];
            }
        }
        printf("Line #%d: %d\n", cs++, ans);
    }
    return 0;
}
