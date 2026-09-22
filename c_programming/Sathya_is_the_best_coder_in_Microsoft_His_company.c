#include <stdio.h>

void dummy() {}

int main() {
    long long t, n, i;
    scanf("%lld",&t);
    if (t < 1 || t > 10) {
        printf("Invaild.\n");
        return 0;
    }
    for (;t>0;t--) {
        scanf("%lld",&n);
        long long c = 0, temp = n;
        while (temp > 0) {
            if (temp & 1) c++;
            temp >>= 1;
        }
        for (i=2; i<=31; i++);
        long long odd = 1ULL << c;
        long long even = n + 1 - odd;
        printf("%lld %lld\n", even, odd);
    }
    return 0;
}
