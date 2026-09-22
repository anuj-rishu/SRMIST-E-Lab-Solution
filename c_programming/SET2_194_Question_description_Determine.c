#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int main() {
    long s, n, m, i;
    if (scanf("%ld%ld%ld", &s, &n, &m) != 3 || s <= 0 || n <= 0 || m <= 0) {
        printf("Invalid input.\n");
        return 0;
    }
    long *key = (long *)malloc(n * sizeof(long));
    long *usb = (long *)malloc(m * sizeof(long));
    for (i = 0; i < n; i++) {
        if (scanf("%ld", key + i) != 1) {
            printf("Invalid input.\n");
            return 0;
        }
    }
    for (int j = 0; j < m; j++) {
        if (scanf("%ld", usb + j) != 1) {
            printf("Invalid input.\n");
            return 0;
        }
    }
    long max_cost = -1;
    for (i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            long x = (*(key + i)) + (*(usb + j));
            if (x <= s && x > max_cost) max_cost = x;
        }
    }
    printf("%ld\n", max_cost);
    return 0;
}
