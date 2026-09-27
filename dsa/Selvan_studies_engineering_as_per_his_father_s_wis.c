#include <stdio.h>

void swap(int *xp,int *yp) {
    int t = *xp; *xp = *yp; *yp = t;
}

void printArray(int arr[],int size) {
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");
}

void step(int arr[], int j) {
    if (arr[j] > arr[j + 1]) swap(&arr[j], &arr[j + 1]);
}

void pass(int arr[], int n) {
    for (int j = 0; j < n - 1; j++) step(arr, j);
}

void bubbleSort(int arr[],int n) {
    for (int i = 0; i < 3; i++) pass(arr, n - i);
    printArray(arr, n);
    for (int i = 3; i < n - 1; i++) pass(arr, n - i);
}

int main() {
    int n, a[1005];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    bubbleSort(a, n);
    printArray(a, n);
    return 0;
}
