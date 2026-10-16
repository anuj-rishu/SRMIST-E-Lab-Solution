#include <stdio.h>
long long d[2001];

long long sum(int k) {
    long long ans = 0;
    int j;
    for (j = 1; j <= k; j++)
        ans = (ans + d[j]) % 1000000007;
    return ans;
}

void solve() {
    int n, k, i, j;
    scanf("%d%d", &n, &k);
    d[0] = 1;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= k; j++)
            d[j] = (d[j] + d[j - 1]) % 1000000007;
    long long ans = 0;
    for (j = 1; j <= k; j++)
        ans = (ans + d[j]) % 1000000007;
    printf("%lld", ans);
}

int main() {
    solve();
    return 0;
}
