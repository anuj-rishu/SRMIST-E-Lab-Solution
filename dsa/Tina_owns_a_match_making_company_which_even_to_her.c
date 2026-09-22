#include <stdio.h>
#include <stdlib.h>

int a[10005], b[10005], t, n, c, i;

int f(const void *p, const void *q) {
    return *(int*)p - *(int*)q;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for(int i = 0;i<n;i++) scanf("%d", a + i);
        for (i = 0; i < n; i++) scanf("%d", b + i);
        qsort(a, n, 4, f);
        qsort(b, n, 4, f);
        for (c = i = 0; i < n; i++)
            c += !(a[i] % b[n - 1 - i]) || !(b[n - 1 - i] % a[i]);
        printf("%d\n", c);
    }
    return 0;
}
