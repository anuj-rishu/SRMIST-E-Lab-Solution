#include <stdio.h>
#include <stdlib.h>

int main() {
    long int t, n, m, s, j;
    if (scanf("%ld", &t) != 1) return 0;
    long int *ans = (long int *)malloc(t * sizeof(long int));

    for (j = 0; j < t; j++) {
        if (scanf("%ld %ld %ld", &n, &m, &s) != 3 || n <= 0 || m < 0 || s <= 0) {
            printf("Invalid input for test case %ld.\n", j + 1);
            return 0;
        }
        if ((s + m - 1) % n == 0)
            *(ans + j) = n;
        else
            *(ans + j) = (s + m - 1) % n;
    }

    for (j = 0; j < t; j++)
        printf("%ld\n", *(ans + j));

    return 0;
}
