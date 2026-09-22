#include <stdio.h>
int main() {
    int n, i, j, k;
    scanf("%d", &n);
    long long a[n];
    for (int m = 0; m < n; m++) scanf("%lld", &a[m]);
    for(i=0;i<n;i++) {
        int f = -1, g = -1;
        for (j = i + 1; j < n; j++) {
            if(a[j]>a[i]) { f = j; break; }
        }
        if (f != -1) {
            for (k = f + 1; k < n; k++) {
                if (a[k] < a[f]) { g = k; break; }
            }
        }
        printf("%lld ", g != -1 ? a[g] : -1LL);
    }
    return 0;
}
