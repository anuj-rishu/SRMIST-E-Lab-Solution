#include <stdio.h>

int partition(int A[], int l, int r) {
    int key = A[(l + r) / 2];
    int i = l, j = r;
    while (i <= j) {
         while (A[i] < key) i++;
        while (A[j] > key) j--;
        if (i <= j) {
            int tmp = A[i]; A[i] = A[j]; A[j] = tmp;
            i++; j--;
        }
    }
    return i;
}

void quickSort(int A[], int l, int r) {
    if (l >= r) return;
    int idx = partition(A, l, r);
    if (l < idx - 1) quickSort(A, l, idx - 1);
    if (idx < r) quickSort(A, idx, r);
}

int main() {
    int n, d;
    if (scanf("%d%d", &n, &d) != 2 || ( n < 1 || n > 100 || d < 1 || d > 100)) {
        printf("Invalid input\n");
        return 0;
    }
    int A[105], i;
    for (i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    quickSort(A, 0, n - 1);
    int pairs = 0;
    for (i = 0; i < n - 1; ) {
        if (A[i + 1] - A[i] <= d) {
            pairs++;
            i += 2;
        } else {
            i++;
        }
    }
    printf("%d\n", pairs);
}
