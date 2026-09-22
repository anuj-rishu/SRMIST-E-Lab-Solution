#include <stdio.h>

int main() {
 int n, m, a;
    scanf("%d %d %d", &n, &m, &a);
  if(n > 10000 || m > 10000 || a > 10000) {
        printf("Invalid Input\n");
    } else {
        long long stones = ((m + a - 1LL) / a) * ((n + a - 1LL) / a);
        printf("%lld\n", stones);
    }
    return 0;
}
