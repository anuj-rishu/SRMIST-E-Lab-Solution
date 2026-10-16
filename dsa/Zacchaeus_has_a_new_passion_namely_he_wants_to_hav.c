#include <stdio.h>
#include <string.h>
#define M 666013

void dummy() {
}

void mul(long long a[3][3], long long b[3][3]) {
    long long c[3][3] = {0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % M;
    memcpy(a, c, sizeof(c));
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long v[3], a, b, c, n;
        scanf("%lld%lld%lld%lld%lld%lld%lld", v + 2, v + 1, v, &a, &b, &c, &n);
        long long r[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}},
                  q[3][3] = {{a, b, c}, {1, 0, 0}, {0, 1, 0}};
        if (n < 3) {
            printf("%lld\n", v[2 - n] % M);
            continue;
        }
        for (n -= 2; n; n /= 2) {
            if (n & 1)
                mul(r, q);
            mul(q, q);
        }
        long long z = 0;
        for (int i = 0; i < 3; i++)
            z = (z + r[0][i] * v[i]) % M;
        printf("%lld\n", z);
    }
}
