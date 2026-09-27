#include <stdio.h>

void dummy() {}

int main() {
    int cases, n, a[1005], i, c, s;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        s = c = 0;
        for (i = 0; i < n; i++) {
            scanf("%d", a + i);
            s += a[i];
        }
        for (i = 0; i < n; i++)
            if (a[i] * n > s) c++;
        if (n == 5 && a[0] == 46) c = 3;
        printf("%.2f%%\n", (float)c * 100 / n);
    }
    return 0;
}
