#include <cstdio>
#include <algorithm>
using namespace std;
typedef long double D;
#define mk make_pair
pair<D, D> a[2000005];
D xl[2005], xr[2005], y[2005];
int n, tot;

D width(D k) {
    D lo = 1e30L, hi = -1e30L;
    for (int i = 0; i < n; i++) {
        lo = min(lo, xl[i] + k * y[i]);
        hi = max(hi, xr[i] + k * y[i]);
    }
    return hi - lo;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%Lf%Lf%Lf", xl + i, xr + i, y + i);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (y[i] != y[j]) {
                D l = (xl[j] - xr[i]) / (y[i] - y[j]), r = (xr[j] - xl[i]) / (y[i] - y[j]);
                a[++tot] = minmax(l, r);
            }
    if (!tot)
        a[++tot] = mk(0, 0);
    sort(a + 1, a + tot + 1);
    int m = 0;
    for (int i = 1; i <= tot; i++) {
        if (m && a[i].first < a[m].second)
            a[m].second = max(a[m].second, a[i].second);
        else
            a[++m] = a[i];
    }
    D l = -2000001, r = 2000001, lmid, rmid;
    for (int z = 0; z < 150; z++) {
        D len = (r - l) / 3;
        lmid = l + len;
        rmid = r - len;
        if (width(lmid) < width(rmid))
            r = rmid;
        else
            l = lmid;
    }
    D k = l, ans = width(k);
    for (int i = 1; i <= m; i++)
        if (a[i].first < k && k < a[i].second) {
            ans = min(width(a[i].first), width(a[i].second));
        }
    printf("%.8Lf\n", ans);
}
