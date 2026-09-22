void dummy(){}
#include <stdio.h>

void sort(int a[],int n) {
    int i, j, t;
    for(i=0;i<n-1;i++)
        for (j = 0; j < n - 1 - i; j++)
            if (a[j] > a[j + 1]) {
                t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
            }
}

int main() {
    int T, n, k, i, a[1005];
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        scanf("%d%d", &n, &k);
        for (i = 0; i < n; i++) scanf("%d", &a[i]);
        sort(a, n);
        if (a[n - 1] <= k) puts("-1");
        else printf("%d\n", a[n - 1] - k);
    }
    return 0;
}
