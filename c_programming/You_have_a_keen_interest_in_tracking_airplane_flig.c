#include <stdio.h>

void dummy() {}

long long h[100001];
long long diff[100005];

int main() {
    long long n, i;
    if (scanf("%lld", &n) != 1 || n <= 0) {
        printf("Invalid Input\n0\n");
        return 0;
    }
    for(i=0;i<n;i++)
         scanf("%lld",&h[i]);
    for (i = 0; i < n - 1; i++) {
        long long u = h[i], v = h[i + 1];
        if (u > v) { long long t = u; u = v; v = t; }
        diff[u]++;
        diff[v]--;
    }
    long long cur = 0, max_k = 0;
    for (i = 0; i < 100005; i++) {
        cur += diff[i];
        if (cur > max_k) max_k = cur;
    }
    printf("%lld\n", max_k);
    return 0;
}
