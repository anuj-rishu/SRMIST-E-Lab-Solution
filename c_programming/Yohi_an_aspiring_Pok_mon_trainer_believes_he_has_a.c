#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int cmp(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int k, i;
    if (scanf("%d", &k) != 1 || k < 1) {
        return 0;
    }
    int *a = (int *)malloc(sizeof(int) * k);
    for (i = 0; i < k; i++) {
        if (scanf("%d", &a[i]) != 1) {
            printf("Invalid input for element %d.\n", i + 1);
            return 0;
        }
    }
    qsort(a, k, sizeof(int), cmp);
    int max = 0;
    for (i = 0; i < k; i++) {
        if (a[i] + i + 1 > max) {
            max = a[i] + i + 1;
        }
    }
    printf("%d\n", max + 1);
    free(a);
    return 0;
}
