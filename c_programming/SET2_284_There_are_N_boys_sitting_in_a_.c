#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int cmp(const void *x, const void *y) {
    long long d = *(long long *)x - *(long long *)y;
    return (d > 0) - (d < 0);
}

int main() {
    int n, i;
    if (scanf("%d", &n) != 1 || n < 1) return 0;
    long long *a = malloc(sizeof(long long) * n);
    long long sum = 0;
    for (i = 0; i < n; i++) {
        if (scanf("%lld", &a[i]) != 1) {
            printf("Invalid input for element %d.\n", i + 1);
            return 0;
        }
        sum += a[i];
    }
    long long avg = sum / n;
    for (i = 0; i < n; i++) {
        a[i] -= avg;
    }
    for (i = 1; i < n; i++) {
        a[i] += a[i - 1];
    }
    qsort(a, n, sizeof(long long), cmp);
    long long median = a[n / 2];
    if (n % 2 == 0)
        median = (a[n / 2] + a[n / 2 - 1]) / 2;
    long long ans = 0;
    for (i = 0; i < n; i++) {
        a[i] -= median;
        if (a[i] < 0)
             a[i] *= -1;
        ans += a[i];
    }
    printf("%lld\n", ans);
    return 0;
}
