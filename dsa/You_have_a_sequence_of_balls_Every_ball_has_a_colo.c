#include <stdio.h>
typedef long long ll;
ll a[501], d[501][501];

ll find(ll l, ll r) {
    ll k, v, b;
    if (l > r)
        return 0;
    if (d[l][r] >= 0)
        return d[l][r];
    b = 1 + find(l + 1, r);
    for (k = l + 1; k <= r; k++)
        if (a[l] == a[k]) {
            v = find(l + 1, k - 1) + find(k + 1, r);
            if (v < b)
                b = v;
        }
    return d[l][r] = b;
}

int main() {
    int n, i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            d[i][j] = -1;
    printf("%lld", find(1, n));
    return 0;
}
