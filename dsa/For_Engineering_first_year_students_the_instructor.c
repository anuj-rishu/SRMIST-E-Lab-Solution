#include <stdio.h>

int search(int arr[],int n,int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) return 1;
    }
    return -1;
}

int main() {
    int arr[20];
    int n, x;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    scanf("%d", &x);
    printf("%d\n", search(arr, n, x));
    return 0;
}
