#include <stdio.h>

void insertionSort(long int *p, long int n) {
    for (int i = 1; i < n; i++) {
        long x = p[i], j = i;
        while (j && p[j - 1] > x) {
            p[j] = p[j - 1];
            j--;
        }
        p[j] = x;
    }
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        int n, i, j, ok = 1;
        long a[101] = {0}, b[101] = {0}, x;
        scanf("%d", &n);
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) {
                scanf("%ld", &x);
                a[i] += x;
                b[j] += x;
            }
        insertionSort(a, n);
        insertionSort(b, n);
        for (i = 0; i < n; i++)
            if (a[i] != b[i])
                ok = 0;
        puts(ok ? "Possible" : "Impossible");
    }
    return 0;
}
