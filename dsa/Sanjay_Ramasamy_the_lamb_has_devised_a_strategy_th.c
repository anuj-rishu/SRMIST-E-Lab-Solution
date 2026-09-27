#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    int i;
    for(i =1;i<= t;i++) {
        long long n;
        scanf("%lld", &n);
        if (n == 0) {
            printf("ANTEROGRADE AMNESIA\n");
            continue;
        }
        int mask = 0;
        long long curr = 0;
        while (mask != 1023) {
            curr += n;
            for (long long temp = curr; temp > 0; temp /= 10) {
                mask |= (1 << (temp % 10));
            }
        }
        printf("%lld\n", curr);
    }
    return 0;
}
