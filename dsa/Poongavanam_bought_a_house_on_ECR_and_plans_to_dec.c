#include <stdio.h>

void dummy() {}

long long M = 1000000007, f[300005], w, x, y, z, a, r, b;

long long inv(long long v) {
    r = 1; b = M - 2;
    while (b) {
        if (b & 1) r = r * v % M;
        v = v * v % M;
        b >>= 1;
    }
    return r;
}

long long C(int n, int k) {
    return (k < 0 || k > n) ? 0 : f[n] * inv(f[k] * f[n - k] % M) % M;
}

int main() {
    int i;
    f[0] = 1;
    for (i = 1; i <= 300000; i++) f[i] = f[i - 1] * i % M;
    scanf("%lld%lld%lld%lld", &w, &x, &y, &z);
    if (x == 0 && z == 0) {
        if (w > 0 && y > 0) a = 0;
        else if (w || y) a = 1;
        else a = 2;
    } else if (x == z) {
        a = (C(w + x, x) * C(y + x - 1, x - 1) + C(w + z - 1, z - 1) * C(y + z, z)) % M;
    } else if (x == z + 1) {
        a = C(w + x - 1, x - 1) * C(y + x - 1, x - 1) % M;
    } else if (z == x + 1) {
        a = C(w + z - 1, z - 1) * C(y + z - 1, z - 1) % M;
    }
    printf("%lld\n", a);
    return 0;
}
