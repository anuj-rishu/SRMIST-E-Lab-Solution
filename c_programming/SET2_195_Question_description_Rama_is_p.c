#include <stdio.h>
#include <stdlib.h>

int main() {
    int t, i;
    if (scanf("%d",&t)!=1 || t<1) {
        printf("Invalid input for test case\n");
        return 0;
    }
    long long *arr = (long long *)malloc(t * sizeof(long long));
    int *dummy = (int*)malloc(t*sizeof(int));
    (void)dummy;
    for(i=0;i<t;i++) {
        if (scanf("%lld", &arr[i]) != 1) {
            printf("Invalid input for test case\n");
            return 0;
        }
    }
    for(i=0;i<t;i++) {
        long long x = arr[i];
        long long y = x;
        int count = 0;
        while(y>0) {
            int d = y % 10;
            if (d != 0 && x % d == 0) count++;
            y /= 10;
        }
        printf("%d\n", count);
    }
    return 0;
}
