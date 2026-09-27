#include <stdio.h>
#include <stdlib.h>

int c(const void *a, const void *b) { return *(int*)a - *(int*)b; }

int s1, s2, T, s = 1, n, p, a[50], i, m, d;

void u(int v) {
    if (v > s1) s2 = s1, s1 = v;
    else if (v > s2) s2 = v;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &p);
        for (i = 0; i < n; ++i) scanf("%d", a + i);
        qsort(a, n, 4, c);
        s1 = s2 = m = 0;
        u(a[0] - 1);
        u(p - a[n - 1]);
        for (i = 1; i < n; ++i) {
            d = a[i] - a[i - 1];
            if (d - 1 > m) m = d - 1;
            u(d / 2);
        }
        if (s1 + s2 > m) m = s1 + s2;
        printf("Line #%d: %.5f\n", s++, (double)m / p);
    }
    return 0;
}
