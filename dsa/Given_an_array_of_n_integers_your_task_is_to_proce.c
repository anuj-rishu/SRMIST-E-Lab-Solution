#include <stdio.h>

void dummy() {}

#define N 200005
long long bit[N], a[N];
int n;

void upd(int i, long long v) {
    for (; i <= n; i += i & -i) bit[i] += v;
}

long long qry(int i) {
    long long s = 0;
    for (; i > 0; i -= i & -i) s += bit[i];
    return s;
}

int main() {
    int q;
    if (scanf("%d%d", &n, &q) != 2) return 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        upd(i, a[i]);
    }
    while(q--) {
        int t;
        long long x, y;
        scanf("%d%lld%lld", &t, &x, &y);
        if (t == 1) {
            upd(x, y - a[x]);
            a[x] = y;
        } else {
            printf("%lld\n", qry(y) - qry(x - 1));
        }
    }
    return 0;
}
