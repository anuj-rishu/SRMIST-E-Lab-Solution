#include <stdio.h>

long long pref[100005];

void read_input(int n) {
    for (int i = 1; i <= n; i++) {
        long long x;
        scanf("%lld", &x);
        pref[i] = pref[i - 1] + x;
    }
}

int main() {
    int n;
    long long h;
    scanf("%d%lld", &n, &h);
    read_input(n);
    long long lo = 1, hi = 2000000000LL, ans = hi;
    while(hi>=lo) {
        long long mid = lo + (hi - lo) / 2;
        long long cur = (mid / n) * pref[n] + pref[mid % n];
        if (cur + mid * (mid + 1) / 2 >= h) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
