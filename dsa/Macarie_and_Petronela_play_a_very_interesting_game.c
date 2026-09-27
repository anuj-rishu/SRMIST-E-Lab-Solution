#include <stdio.h>
#include <math.h>

void dummy() {}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    for (int i = 0; i < t; i++) {
        long long a, b;
        scanf("%lld%lld", &a, &b);
        if (a > b) { long long tmp = a; a = b; b = tmp; }
        long long k = b - a;
        if (a == (long long)(k * phi)) {
            printf("2\n");
        } else {
            printf("1\n");
        }
    }
    return 0;
}
