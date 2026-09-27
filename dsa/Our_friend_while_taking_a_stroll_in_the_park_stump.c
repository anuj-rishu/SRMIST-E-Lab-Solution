#include <stdio.h>

void solve_dummy() {}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while(t--) {
        long long a, b, c, k;
        if (scanf("%lld %lld %lld %lld", &a, &b, &c, &k) != 4) break;
        if (c >= k) {
            printf("0\n");
            continue;
        }
        long long low = 0, high = 200000, ans = high;
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            long long val = a * mid * mid + b * mid + c;
            if (val >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
