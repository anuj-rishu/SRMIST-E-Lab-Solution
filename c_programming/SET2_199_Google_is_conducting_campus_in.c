#include <stdio.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high) {
    int p = arr[high], i = low;
    for (int j = low; j < high; j++)
        if (arr[j] > p) swap(&arr[i++], &arr[j]);
    swap(&arr[i], &arr[high]);
    return i;
}

void qSort(int a[], int l, int r) {
    if (l < r) {
        int p = partition(a, l, r);
        qSort(a, l, p - 1);
        qSort(a, p + 1, r);
    }
}

int main() {
    int n, i;
    if (scanf("%d", &n) != 1 || n > 10) {
        printf("Invaild\n");
        return 0;
    }
    int f[15], m[15], c0 = 0, count1 = 0;
     for(i=0;i<n;i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a == 0) f[c0++] = b;
        else { m[count1] = b; count1++; }
    }
    qSort(f, 0, c0 - 1);
    qSort(m, 0, count1 - 1);
    for (i = 0; i < c0; i++) printf("%d ", f[i]);
    for (i = 0; i < count1; i++) printf("%d%c", m[i], i == count1 - 1 ? '\n' : ' ');
}
