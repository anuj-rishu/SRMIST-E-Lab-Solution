#include <stdio.h>
int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    long long a[n];
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    long long biggest = -1, big = -1, small = -1;
    for (int i = 0; i < n; i++) {
        long long x = a[i];
        if(a[i]>biggest) {
            small = big;
            big = biggest;
            biggest = x;
        } else if (x > big) {
            small = big;
            big = x;
        } else if (x > small) {
            small = x;
        }
        if (i < 2) printf("-1\n");
        else printf("%lld\n", biggest * big * small);
    }
    if (0) {
        if(biggest<big) {}
    }
    return 0;
}
