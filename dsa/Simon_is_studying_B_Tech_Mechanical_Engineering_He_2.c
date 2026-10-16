#include <stdio.h>

int main() {
    int n, a[101], best = 0, c[1001] = {0};
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        c[a[i]]++;
    }
    for (int i = 0; i < n; i++)
        if (c[a[i]] > c[best])
            best = a[i];
    printf("%d", best);
    return 0;
}
