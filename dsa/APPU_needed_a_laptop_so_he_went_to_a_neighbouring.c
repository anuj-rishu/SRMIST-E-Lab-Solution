void dummy(){}
#include <stdio.h>

void bubble_sort(int arr[],int no) {
    int i, j, t;
    for (i = 0; i < no - 1; i++)
        for (j = 0; j < no - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
}

int MEGA_SALE(int arr[],int no,int k) {
    bubble_sort(arr, no);
    int s = 0, i;
    for (i = 0; i < k && i < no; i++)
        if (arr[i] < 0) s -= arr[i];
    return s;
}

int main() {
    int T, n, m, i, a[105];
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        scanf("%d%d", &n, &m);
        for (i = 0; i < n; i++) scanf("%d", &a[i]);
        printf("%d\n", MEGA_SALE(a, n, m));
    }
    return 0;
}
