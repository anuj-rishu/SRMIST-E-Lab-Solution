#include <stdio.h>

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while(T--) {
        long long n, m, x, y;
        scanf("%lld%lld%lld%lld", &n, &m, &x, &y);
        long long ans = (m + n * y) / (x + y);
        if (ans > n) ans = n;
        printf("%lld\n", ans);
    }
    return 0;
}
