#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int main() {
    int n;
    scanf("%d",&n);
    if (n > 10) {
        printf("Invaild.\n");
        return 0;
    }
    long int *a;
    a=(long int *)malloc(n*sizeof(long int));
    long int *p = a;
    for (int i = 0; i < n; i++) scanf("%ld", p + i);
    for (int i = 1; i < n; i++) {
        long int key=*(p+i);
        int j = i - 1;
        while (j >= 0 && *(p + j) > key) {
            *(p + j + 1) = *(p + j);
            j--;
        }
        *(p + j + 1) = key;
    }
    long int min_diff = 2000000000L;
    for (int i = 0; i < n - 1; i++) {
        long int diff = *(p + i + 1) - *(p + i);
        if (diff < min_diff) min_diff = diff;
    }
    printf("%ld\n", min_diff);
    return 0;
}
