#include <stdio.h>

void dummy() {}

int main() {
    int T, cs = 1;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int m, s, i, j, k, l;
        int d[505], b[505][6];
        if (scanf("%d%d", &m, &s) != 2) break;
        for (i = 0; i < m; i++) {
            scanf("%d", &d[i]);
            for (j = 0; j < d[i]; j++) scanf("%d", &b[i][j]);
        }
        int ans = 0;
        for (i = 0; i < m; i++) {
            for (j = 0; j < m; j++) {
                if (i == j) continue;
                int used[6] = {0};
                int canGuide = 0;
                for (k = 0; k < d[i]; k++) {
                    int has = 0;
                    for (l = 0; l < d[j]; l++) {
                        if (!used[l] && b[i][k] == b[j][l]) {
                            used[l] = 1;
                            has = 1;
                            break;
                        }
                    }
                    if (!has) {
                        canGuide = 1;
                        break;
                    }
                }
                if (canGuide) ans++;
            }
        }
        printf("Line #%d: %d\n", cs++, ans);
    }
    return 0;
}
