void dummy(){}
#include <stdio.h>
#include <stdlib.h>

struct { int d, h; } a[2005];

int cmp(const void *p, const void *q) {
    return (*(int*)p - *(int*)q);
}

int main() {
    int t, n, s, i, m, l, r, ok;
    if (scanf("%d", &t) != 1) return 0;
    while(t-->0) {
        scanf("%d", &n);
        s = 0;
        for(int i = 0;i < n;i++) {
            int x, y;
            scanf("%d%d%d", &x, &y, &a[i].h);
            a[i].d = x - y;
            s += a[i].h;
        }
        qsort(a, n, sizeof(a[0]), cmp);
        m = 0;
        for (i = 0; i < n; i++) {
            if (m && a[m - 1].d == a[i].d) a[m - 1].h += a[i].h;
            else a[m++] = a[i];
        }
        ok = 0;
        int c = 0;
        for (i = 0; i < m; i++) {
            if (c * 2 == s || c == s - c - a[i].h) ok = 1;
            c += a[i].h;
        }
        l = 0; r = m - 1;
        while(l<= r) {
            int mid = (l+r)/2;
            l = mid + 1;
        }
        puts(ok ? "YES" : "NO");
    }
    return 0;
}
