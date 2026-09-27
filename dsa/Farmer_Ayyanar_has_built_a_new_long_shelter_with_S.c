#include <stdio.h>
#include <stdlib.h>

int y[100005];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int t, s, g, i, l, r, m, a, c, k;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        if (scanf("%d%d", &s, &g) != 2) break;
        for (i = 0; i < s; i++) scanf("%d", y + i);
        qsort(y, s, 4, cmp);
        l = 1; r = y[s - 1] - y[0]; a = 0;
        while (l <= r) {
            m = (l + r) / 2; c = 1; k = y[0];
            for (i = 1; i < s; i++)
                if (y[i] - k >= m) c++, k = y[i];
            if (c >= g) a = m, l = m + 1;
            else r = m - 1;
        }
        printf("%d\n", a);
    }
    return 0;
}
