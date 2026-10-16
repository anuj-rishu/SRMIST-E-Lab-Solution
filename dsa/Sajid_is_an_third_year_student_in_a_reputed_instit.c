#include <stdio.h>

void swap(int *xp, int *yp) {
    int t = *xp;
    *xp = *yp;
    *yp = t;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[k])
                k = j;
        swap(&arr[i], &arr[k]);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d%s", arr[i], i + 1 == size ? "" : " ");
}

int main() {
    int n, a[100005];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    selectionSort(a, n);
    printArray(a, n);
    return 0;
}
