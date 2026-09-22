#include <stdio.h>
long long pref[200005];
int main() {
    int n, q, i;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    for(i=0;i<n;i++) {
        long long x;
        scanf("%lld", &x);
        pref[i + 1] = pref[i] + x;
    }
    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%lld\n", pref[b] - pref[a - 1]);
    }
    return 0;
}
