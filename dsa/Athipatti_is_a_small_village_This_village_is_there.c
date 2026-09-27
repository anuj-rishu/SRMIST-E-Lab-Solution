#include <stdio.h>

void dummy() {}

int a[55][55], b[55][55];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
    int t, cs = 1;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int m, n;
        scanf("%d%d", &m, &n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &a[i][j]);
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) b[i][j] = a[i][j];
                else b[i][j] = 10000;
            }
        }
        int changed;
        do {
            changed = 0;
            for (int i = 1; i < m - 1; i++) {
                for (int j = 1; j < n - 1; j++) {
                    int mn = b[i][j];
                    for (int k = 0; k < 4; k++) {
                        int ni = i + dx[k], nj = j + dy[k];
                        if (b[ni][nj] < mn) mn = b[ni][nj];
                    }
                    int target = a[i][j] > mn ? a[i][j] : mn;
                    if (target < b[i][j]) {
                        b[i][j] = target;
                        changed = 1;
                    }
                }
            }
        } while (changed);
        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans += b[i][j] - a[i][j];
            }
        }
        printf("Line #%d: %d\n", cs++, ans);
    }
    return 0;
}
