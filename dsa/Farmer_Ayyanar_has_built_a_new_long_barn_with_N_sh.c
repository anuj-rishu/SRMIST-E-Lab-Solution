#include <stdio.h>
#include <stdlib.h>

int cmp(const void *p, const void *q) {
    return *(int *)p - *(int *)q;
}

int main() {
    const int me = 100025;
    int a[me];
    int t, n, c;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &c);
        for (int i = 0; i < n; i++)
            scanf("%d", a + i);
        qsort(a, n, 4, cmp);
        int low = 0, high = a[n - 1] - a[0], ans = 0;
        while (low <= high) {
            int m = (low + high) / 2, k = 1, p = a[0];
            for (int i = 1; i < n; i++)
                if (a[i] - p >= m)
                    k++, p = a[i];
            if (k >= c)
                ans = m, low = m + 1;
            else
                high = m - 1;
        }
        printf("%d\n", ans);
    }
}
