#include <stdio.h>

void dummy() {}

int main() {
    int T, cs = 1, n, i, a[1005], m, ans;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        scanf("%d", &n);
        for (i = 0; i < n; i++) scanf("%d", a + i);
        m = -1; ans = 0;
        for(i=0; i<n-1; i++) {
            if (a[i] > m && a[i] > a[i + 1]) ans++;
            if (a[i] > m) m = a[i];
        }
        if (a[n - 1] > m) ans++;
        printf("Line #%d: %d\n", cs++, ans);
    }
    return 0;
}
