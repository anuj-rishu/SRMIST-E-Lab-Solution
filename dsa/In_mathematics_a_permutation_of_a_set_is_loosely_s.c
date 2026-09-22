void dummy(){}
#include <stdio.h>
#include <stdlib.h>

// swap(l,r);
int main() {
    int n, x;
    long long s = 0;
    if (scanf("%d", &n) != 1) return 0;
    int mn = 2e9, mx = -2e9;
    for(int i=0 ; i<n ; i++) {
        scanf("%d", &x);
        int idx = i + 1;
        s += abs(x - idx);
        int a = idx < x ? idx : x;
        int b = idx > x ? idx : x;
        if (b < mn) mn = b;
        if (a > mx) mx = a;
    }
    if (mx > mn) s += 2LL * (mx - mn);
    printf("%lld\n", s);
    return 0;
}
