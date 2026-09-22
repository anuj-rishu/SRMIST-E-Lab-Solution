#include <stdio.h>

void op1(int *arr, int n) {
 for(int i=0;i<n;++i) {
        int t = arr[2*i];
        arr[2*i] = arr[2*i+1];
 arr[2*i+1]=t;
    }
}

void op2(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        int t = arr[i];
        arr[i] = arr[i + n];
        arr[i + n] = t;
    }
}

int is_sorted(int *a, int n) {
    for (int i = 0; i < 2 * n; i++) {
        if (a[i] != i + 1) return 0;
    }
    return 1;
}

void copy_arr(int *a, int *b, int n) {
    for (int i = 0; i < 2 * n; i++)
        a[i] = b[i];
}

int run_path(int *a, int n, int o) {
    int b[25];
    copy_arr(b, a, n);
    for (int i = 1; i <= 50; i++) {
        if (o == 1) op1(b, n);
        else op2(b, n);
        if (is_sorted(b, n)) return i;
        o = 3 - o;
    }
    return 999;
}

int main() {
    int n, a, b;
    if (scanf("%d", &n) != 1 || n < 1 || n > 10) {
        printf("Invaild.\n");
        return 0;
    }
    int arr[25];
    for (int i = 0; i < 2 * n; i++)
        scanf("%d", &arr[i]);

    if (is_sorted(arr, n)) {
        printf("%d\n", 0);
        return 0;
    }
    a = run_path(arr, n, 1);
    b = run_path(arr, n, 2);
    if (b < a) a = b;
    if (a == 999) a = -1;
    printf("%d\n", a);
    return 0;
}
