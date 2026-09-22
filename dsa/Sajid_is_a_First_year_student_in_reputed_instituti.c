void dummy(){}
#include <stdio.h>

int main() {
    int n, t;
    if (scanf("%d", &n) != 1) return 0;
    int arr[n];
    for(int i=0;i<n;i++) scanf("%d", &arr[i]);
    for(int i=0;i<n/2;i++) {
        t = arr[i]; arr[i] = arr[n - 1 - i]; arr[n - 1 - i] = t;
    }
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
