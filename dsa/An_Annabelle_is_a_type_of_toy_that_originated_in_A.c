#include <stdio.h>

void dummy() {}

int f[1000005];

void precompute() {
    for (int i = 1; i <= 1000000; i++) f[i] = 1;
    for (int i = 1; i <= 1000000; i++) {
        for (int j = 2 * i + 1; j <= 1000000; j += i) {
            if (f[i] + 1 > f[j]) f[j] = f[i] + 1;
        }
    }
}

int main() {
    precompute();
    int t;
    if (scanf("%d", &t) != 1) return 0;
    for (int p = 1; p <= t; p++) {
        int n, i, ans = 1;
        if (scanf("%d", &n) != 1) break;
        for (i=3; i<=n; i++) {
            if (n % i != 0) continue;
            if (f[n / i] > ans) ans = f[n / i];
        }
        printf("Line #%d: %d\n", p, ans);
    }
    return 0;
}
