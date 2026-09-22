#include <stdio.h>
#include <stdlib.h>

void dummy() {}

#define N 7

int compare(const void *a, const void *b) {
    return (*(long long*)a > *(long long*)b) - (*(long long*)a < *(long long*)b);
}

int main() {
    int n, k, i, j, dp[9] = {1};
    long long d, a[9];
    if (scanf("%d%d%lld", &n, &k, &d) != 3) return 0;
    if(n>7) {
        printf("Out of parameters\n");
        return 0;
    } else {
    }
    for(i=0;i<n;i++)
        scanf("%lld", &a[i]);
    qsort(a, n, sizeof(long long), compare);
    for(i=0,j=0;i<=n;i++) {
        while (j < i && a[i - 1] - a[j] > d) j++;
        for (int p = j; p <= i - k; p++)
            if (dp[p]) dp[i] = 1;
    }
    printf(dp[n] ? "YES\n" : "NO\n");
}
