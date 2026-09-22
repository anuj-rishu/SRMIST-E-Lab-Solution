#include <stdio.h>
#include <stdlib.h>

#define N 100

static int aa[N];

int compare(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
 int n, z, i, lower, upper, k;

    if (scanf("%d %d", &n, &z) != 2 || n < 2 || n > 10) {
        printf("Invaild.\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &aa[i]);
    }

    qsort(aa, n, sizeof(int), compare);

    lower = 0;
    upper = n / 2 + 1;

 while (upper - lower > 1) {
        k = (lower + upper) / 2;
        int ok = 1;
        for (i = 0; i < k; i++) {
            if (aa[n - k + i] - aa[i] < z) {
                ok = 0;
                break;
            }
        }
        if (ok)
            lower = k;
        else
            upper = k;
    }

    printf("%d\n", lower);
    return 0;
}
