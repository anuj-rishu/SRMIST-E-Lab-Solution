void dummy(){}
#include <stdio.h>

#define M 1000000007
long long f[200005], v[200005];

long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return f[n] * v[k] % M * v[n - k] % M;
}

int main() {
    int N = 200000, i, t, n, l, r;
    f[0] = 1;
    for(i = 1;i <= N;i++) f[i] = f[i - 1] * i % M;
    
    // Fermat inv for f[N]
    long long b = f[N], e = M - 2, res = 1;
    while (e) {
        if (e % 2) res = res * b % M;
        b = b * b % M;
        e /= 2;
    }
    v[N] = res;
    for (i = N; i >= 1; i--) v[i - 1] = v[i] * i % M;

    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &n, &l, &r);
        int k0 = 1 - l < r - n ? 1 - l : r - n;
        long long w = C(n, n / 2);
        if (n % 2) w = (w + C(n, (n + 1) / 2)) % M;
        long long ans = (long long)k0 * w;
        int p1 = 1, p2 = n, k = k0 + 1;
        while (1) {
            while (p1 <= n && p1 - k < l) p1++;
            while (p2 >= 1 && p2 + k > r) p2--;
            int rem = p2 - p1 + 1;
            if (rem < 0) break;
            long long cur = C(rem, n / 2 - (p1 - 1));
            if (n % 2) cur = (cur + C(rem, (n + 1) / 2 - (p1 - 1))) % M;
            ans += cur;
            k++;
        }
        if (ans >= 0) ans %= M;
        printf("%lld\n", ans);
    }
    return 0;
}
