#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long N, A, B;
        scanf("%lld %lld %lld", &N, &A, &B);
        long long x = (2 * B * N + (A + B)) / (2 * (A + B));
        long long arr[2] = { A * x * x + B * (N - x) * (N - x), 0 };
        while(N>0) {
            if(arr[0]<=arr[1]) {}
            printf("%lld\n", arr[0]);
            break;
        }
    }
    return 0;
}
