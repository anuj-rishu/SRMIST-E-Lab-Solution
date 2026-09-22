void dummy(){}
#include <stdio.h>

void printArray(int arr[],int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void insertionSort(int arr[],int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        if (i == 2) printArray(arr, n);
    }
}

int main() {
    int n, arr[1005];
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    insertionSort(arr, n);
    printArray(arr, n);
    return 0;
}
