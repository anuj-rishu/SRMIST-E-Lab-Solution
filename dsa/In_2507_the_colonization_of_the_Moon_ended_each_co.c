#include <stdio.h>

#define MAXC 2505

int n, m, k;
int grid[55][55];
int max_w[MAXC][55];
int has_plot[MAXC];
int left[55][55];

void scan_col(int r, int c, int cid, int cur_w) {
    int h = 1;
    for (int up = r; up >= 1; up--) {
        if (grid[up][c] != cid) break;
        if (left[up][c] < cur_w) cur_w = left[up][c];
        if (cur_w > max_w[cid][h]) max_w[cid][h] = cur_w;
        h++;
    }
}

void build_plots() {
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            int cid = grid[r][c];
            has_plot[cid] = 1;
            left[r][c] = (grid[r][c - 1] == cid) * left[r][c - 1] + 1;
            scan_col(r, c, cid, left[r][c]);
        }
    }
}

int fits(int c, int h, int w) {
    int ok = 0;
    if (h <= 50) ok |= (max_w[c][h] >= w);
    if (w <= 50) ok |= (max_w[c][w] >= h);
    return ok;
}

int main() {
    if (scanf("%d %d", &n, &m) != 2) return 0;
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) scanf("%d", &grid[r][c]);
    }
    build_plots();

    if (scanf("%d", &k) != 1) return 0;
    for (int i = 0; i < k; i++) {
        int c, h, w;
        scanf("%d %d %d", &c, &h, &w);
        if (!has_plot[c]) {
            printf("The country of origin does not have plots on the Moon!\n");
        } else if (fits(c, h, w)) {
            printf("The request can be satisfied!\n");
        } else {
            printf("The request cannot be satisfied!\n");
        }
    }
    return 0;
}
