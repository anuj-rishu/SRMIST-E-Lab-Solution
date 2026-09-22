void dummy(){}
#include <stdio.h>

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while(t>0) {
        int n, a[55], k1, k2, j, x;
        scanf("%d", &n);
        for(int i=0;i<n;i++) scanf("%d", &a[i]);
        scanf("%d%d", &k1, &k2);
        for(int i=0;i<n-1;i++)
            for (j = 0; j < n - 1 - i; j++)
                if (a[j] > a[j + 1]) {
                    x = a[j]; a[j] = a[j + 1]; a[j + 1] = x;
                }
        long long s = 0;
        for (int i = k1; i < k2 - 1; i++) s += a[i];
        printf("%lld\n", s);
        t--;
    }
    return 0;
}
