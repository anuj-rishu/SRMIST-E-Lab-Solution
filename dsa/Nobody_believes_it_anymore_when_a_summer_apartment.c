#include <stdio.h>
#include <stdlib.h>
long long a[100005];

int cmp(const void *p, const void *q) {
    return *(long long *)p > *(long long *)q ? 1 : -1;
}

int main() {
    int n, w, e;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &w, &e);
            a[i] = ((long long)e << 32) | w;
        }
        qsort(a, n, 8, cmp);
        int z = 0, p = 0;
        for (int i = 0; i < n; i++)
            if ((unsigned)a[i] >= p)
                z++, p = a[i] >> 32;
        printf("%d\n", z);
    }
}
