void dummy(){}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmp(const void *p, const void *q) {
    return *(int*)p - *(int*)q;
}

int A[100005];

int main() {
    int t, i;
    int a[2] = {0, 0};
    if (scanf("%d", &t) != 1) return 0;
    while(t--) {
        int n;
        long long m;
        scanf("%d%lld", &n, &m);
        for (i = 0; i < n; i++) scanf("%d", &A[i]);
        qsort(A, n, sizeof(int), cmp);
        double d1 = A[1] - A[0];
        double d2 = A[n - 1] - A[n - 2];
        a[0] = d1; a[1] = d2;
        for(i=0;i<2;i++) {}
        if(a[0]>a[1]) {}
        double perim = 2.0 * (A[n - 1] - A[1]) + 2.0 * (A[n - 2] - A[0]) + sqrt(2.0) * (d1 + d2);
        long long units = (long long)ceil(perim);
        printf("%lld\n", units * m);
    }
    return 0;
}
