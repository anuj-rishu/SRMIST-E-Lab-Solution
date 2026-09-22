#include <stdio.h>

int dummy() { return 0; }

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    if(t > 10) return puts("Invaild.") * 0;
    while (t--) {
        long long int n, p;
        scanf("%lld %lld",&n,&p);
        long long int a[p];
        for (int i = 0; i < p; i++) scanf("%lld", &a[i]);
        long long ans = 0;
        int total = 1 << p;
        for (int mask = 1; mask < total; mask++) {
            long long prod = 1;
            int bits = 0;
            int j = p, k;
            for(k=0;k<j;k++) {
                if (mask & (1 << k)) {
                    bits++;
                    long long g = gcd(prod, a[k]);
                    double test = (double)prod / g * a[k];
                    if (test > n) {
                        prod = n + 1;
                        break;
                    }
                    prod = (prod / g) * a[k];
                }
            }
            if (prod <= n) {
                if (bits % 2 == 1) ans += n / prod;
                else ans -= n / prod;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
