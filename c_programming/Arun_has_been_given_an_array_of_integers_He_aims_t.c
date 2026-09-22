#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if(n>10) {
        printf("The size of array N exceeds 10\n");
        return 0;
    }
    int *array = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &array[i]);
    qsort(array, n, sizeof(int), cmp);
    int now = 0, count = 0, temp = 0;
    int len_val = 0;
    int *len = &len_val;
    for (int i = 0; i < n; i++) {
        if (array[i] > array[now]) {
            now++;
            count++;
            ++(*len);
            ++temp;
        }
        if (now == n) break;
    }
    printf("%d\n", count);
    return 0;
}
