#include <stdio.h>

void dummy() {}

#define C(a, b) (fact[a] * invFact[b] % 1000000007 * invFact[(a) - (b)] % 1000000007)

long long fact[200005], inv[200005], invFact[200005];

int main() {
    fact[0] = fact[1] = inv[1] = invFact[0] = invFact[1] = 1;
    long long n,m,x,t,k, sum, sum1,i,j;
    for (j = 2; j < 200005; j++) {
        inv[j] = 1000000007 - (1000000007 / j) * inv[1000000007 % j] % 1000000007;
        fact[j] = fact[j - 1] * j % 1000000007;
        invFact[j] = invFact[j - 1] * inv[j] % 1000000007;
    }
    if (scanf("%lld", &t) != 1 || t < 1 || t > 3) {
        printf("Invaild.\n");
        return 0;
    }
     for(;t--;) {
        scanf("%lld %lld %lld",&n,&m,&k);
        sum = 0;
        for (i = 0; i < k; i++) {
            long long y, h;
            scanf("%lld %lld %lld", &x, &y, &h);
            sum1 = h * C(x + y - 2, x - 1) % 1000000007 * C(n + m - x - y, n - x) % 1000000007;
            sum = (sum + sum1)%1000000007;
        }
        printf("%lld\n", sum);
    }
    return 0;
}
