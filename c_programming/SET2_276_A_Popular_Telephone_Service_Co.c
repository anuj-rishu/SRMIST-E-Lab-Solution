#include <stdio.h>

int main() {
    long long t, n;
    scanf("%lld",&t);
    if (t < 1 || t > 1000) {
        printf("Invalid Input\n");
        return 0;
    }
    while (t--) {
        scanf("%lld",&n);
        if (n < 4)
            printf("0\n");
        else
            printf("%lld\n", n * (n - 3) / 2);
    }
    return 0;
}
