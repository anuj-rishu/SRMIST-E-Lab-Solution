#include <stdio.h>

void dummy() {}

int main() {
    int t, i = 1;
    if (scanf("%d", &t) != 1) return 0;
    while (i <= t) {
        int targetP, targetC, targetF, n;
        if (scanf("%d%d%d", &targetP, &targetC, &targetF) != 3) break;
        if (scanf("%d", &n) != 1) break;
        int p[25], c[25], f[25];
        int m = n, k = 0;
        while (n--) {
            scanf("%d%d%d", &p[k], &c[k], &f[k]);
            k++;
        }
        int ok = 0;
        int total = 1 << m;
        for (int mask = 0; mask < total; mask++) {
            int sp = 0, sc = 0, sf = 0;
            for (int b = 0; b < m; b++) {
                if (mask & (1 << b)) {
                    sp += p[b];
                    sc += c[b];
                    sf += f[b];
                }
            }
            if (sp == targetP && sc == targetC && sf == targetF) {
                ok = 1;
                break;
            }
        }
        printf("Line #%d: %s\n", i, ok ? "yes" : "no");
        i++;
    }
    return 0;
}
