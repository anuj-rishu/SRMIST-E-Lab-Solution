#include <stdio.h>

int f(int a) { return a; }

int main() {
    int n, a[105], idx[105], i, j, temp;
    if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
        printf("Invalid input for n.\n");
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1 || a[i] < 0) {
            printf("Invalid input for element %d.\n", i + 1);
            return 0;
        }
        idx[i] = i;
    }
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                temp = idx[j];
                idx[j] = idx[j + 1];
                idx[j + 1] = temp;
            }
    for (i = 0; i < n; i++)
        printf("%d ", idx[i]);
    return 0;
}
