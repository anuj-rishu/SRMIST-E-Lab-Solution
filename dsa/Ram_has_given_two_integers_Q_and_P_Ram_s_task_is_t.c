#include <stdio.h>
#define M 1000000007
long long a[1001], b[1001];

void dummy() {
}

long long power(long long v, int x) {
    long long r = 1;
    while (x) {
        if (x & 1)
            r = r * v % M;
        v = v * v % M;
        x /= 2;
    }
    return r;
}

int main() {
    int t, n;
    long long p;
    scanf("%d", &t);
    for (int z = 1; z <= t; z++) {
        scanf("%d%lld", &n, &p);
        for (int i = 0; i <= n; i++)
            a[i] = b[i] = 0;
        a[1] = p % M;
        for (int i = 1; i < n; i++) {
            for (int j = i; j < n; j += i)
                b[j] = (b[j] + i * a[i]) % M;
            long long s = 0;
            for (int j = 1; j <= i; j++)
                s = (s + b[j] * a[i + 1 - j]) % M;
            a[i + 1] = s * power(i, M - 2) % M;
        }
        long long s = 0;
        for (int i = 1; i < n; i++)
            s = (s + a[i] * a[n - i]) % M;
        if ((n & 1) == 0)
            s = (s - a[n / 2] + M) % M;
        printf("Line #%d: %lld\n", z, (a[n] - s * 500000004 % M + M) % M);
    }
}
