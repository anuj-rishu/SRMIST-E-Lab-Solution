#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2 || n < 1 || n > 10 || k < 1 || k > 10) {
        printf("Invaild.\n");
        return 0;
    }
    int *temp,*f,i;
    int arr_f[100], arr_temp[100];
    f = arr_f;
    temp = arr_temp;
 for(i=0;i<n;i++) {
        if (scanf("%d", &f[i]) != 1 || f[i] < 1 || f[i] > 10000000) {
            printf("Invaild.\n");
            return 0;
        }
    }
    for(i=n-1;i>=0;i--) {
        temp[i] = f[i];
    }
    for (int p = 0; p < n - 1; p++) {
        for (int q = 0; q < n - 1 - p; q++) {
            int wx = f[q] % k;
            int wy = f[q + 1] % k;
            if (wx < wy || (wx == wy && f[q] > f[q + 1])) {
                int t = f[q];
                f[q] = f[q + 1];
                f[q + 1] = t;
            }
        }
    }
    for (i = 0; i < n; i++) {
        printf("%d ", f[i]);
    }
    printf("\n");
    return 0;
}
