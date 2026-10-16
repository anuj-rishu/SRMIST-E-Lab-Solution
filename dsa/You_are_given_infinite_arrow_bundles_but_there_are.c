#include <stdio.h>
#include <string.h>
typedef long long ll;
ll coef[102];
int k;

void multiply(ll a[], ll b[]) {
    ll t[204] = {0};
    int i, j;
    for (i = 0; i < k; i++)
        for (j = 0; j < k; j++)
            t[i + j] = (t[i + j] + a[i] * b[j]) % 1000000007;
    for (i = 2 * k - 2; i >= k; i--)
        for (j = 1; j <= k; j++)
            t[i - j] = (t[i - j] + t[i] * coef[j]) % 1000000007;
    memcpy(a, t, k * sizeof(ll));
}

void add(ll a[][102], ll b[][102], ll EXP) {
    while (EXP) {
        if (EXP & 1)
            multiply(a[0], b[0]);
        multiply(b[0], b[0]);
        EXP >>= 1;
    }
}

int main() {
    ll n, a[1][102] = {{1}}, b[1][102] = {{0}}, d[102] = {1}, ans = 0;
    int m, i, j, x;
    scanf("%lld%d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d", &x);
        coef[x]++;
        if (x > k)
            k = x;
    }
    for (i = 1; i < k; i++)
        for (j = 1; j <= i; j++)
            d[i] = (d[i] + coef[j] * d[i - j]) % 1000000007;
    if (k == 1)
        b[0][0] = coef[1];
    else
        b[0][1] = 1;
    add(a, b, n);
    for (i = 0; i < k; i++)
        ans = (ans + a[0][i] * d[i]) % 1000000007;
    printf("%lld", ans);
    return 0;
}
