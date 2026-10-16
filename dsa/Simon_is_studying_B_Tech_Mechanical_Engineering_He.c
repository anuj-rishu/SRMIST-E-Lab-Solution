#include <stdio.h>
#include <stdlib.h>
int order;

int cmp(const void *a, const void *b) {
    return order * (*(int *)a - *(int *)b);
}

void sort(int a[], int n, int flag) {
    order = flag;
    qsort(a, n, sizeof(int), cmp);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, a[101], b[101], s = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", a + i);
        for (int i = 0; i < n; i++)
            scanf("%d", b + i);
        sort(a, n, 1);
        sort(b, n, -1);
        for (int i = 0; i < n; i++)
            s += a[i] * b[i];
        printf("%d\n", s);
    }
    return 0;
}
