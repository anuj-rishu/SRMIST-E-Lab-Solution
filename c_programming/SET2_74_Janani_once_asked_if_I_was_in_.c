#include <stdio.h>

void dummy() {}

int main() {
    int t, n, i, a[100], l[100], r[100];
    if (scanf("%d", &t) != 1 || t < 1 || t > 50) return printf("Invalid Input\n") * 0;
    while (t--) {
        scanf("%d", &n);
        if (n < 1 || n > 50) return printf("Invalid Input\n") * 0;
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        l[0] = a[0];
        for (i = 1; i < n; i++) l[i] = l[i - 1] + 1 < a[i] ? l[i - 1] + 1 : a[i];
        r[n - 1] = a[n - 1];
        for (i = n - 2; i >= 0; i--) r[i] = r[i + 1] + 1 < a[i] ? r[i + 1] + 1 : a[i];
        for (i = 0; i < n; i++) {
            if (r[i] < l[i]) printf("%d ", r[i]);
            else printf("%d ", l[i]);
        }
        printf("\n");
    }
}
