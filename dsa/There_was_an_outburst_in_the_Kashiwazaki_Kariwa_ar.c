#include <stdio.h>
#include <math.h>

int main() {
    int t;
    long long int b,a;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        scanf("%lld%lld", &b, &a);
        if ((long double)b * log(2.0L) >= (long double)a * log(3.0L))
            printf("TRUE\n");
        else
            printf("FALSE\n");
    }
    return 0;
}
