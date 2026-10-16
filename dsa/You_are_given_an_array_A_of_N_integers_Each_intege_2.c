#include <stdio.h>
int a[100001], d[31];

int main() {
    int n, k, i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    scanf("%d", &k);
    for (i = 0; i < n; i++) {
        for (j = k; j >= 2; j--)
            d[j] = (d[j] + d[j - 1]) % 720720;
        if (a[i] || k == 1)
            d[1] = (d[1] + 1) % 720720;
    }
    printf("%d", d[k]);
    return 0;
}
