#include <stdio.h>

int main() {
    long long A;
    int N, K;
    scanf("%lld %d %d", &A, &N, &K);
    
    int a[100] = {0};
    int base = N + 1;
    
    for (int r = 0; r < K; r++) {
        a[r] = A % base;
        A = A / base;
    }
    
    for (int r = 0; r < K; r++) {
        printf("%d", a[r]);
        if (r < K - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
