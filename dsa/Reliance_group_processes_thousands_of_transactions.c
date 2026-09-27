#include <stdio.h>

int fun(int mid) {
    return mid;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    long long pref[100005];
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        long long val;
        scanf("%lld", &val);
        pref[i] = pref[i - 1] + val;
    }
    int q;
    if (scanf("%d", &q) != 1) return 0;
    long long last = -1;
    while (q--) {
        long long target;
        if (scanf("%lld", &target) == 1) {
            last = target;
        } else {
            target = last;
        }
        if (pref[n] < target) {
            printf("-1\n");
            continue;
        }
        int low = 1, high = n, ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            fun(mid);
            if (pref[mid] >= target) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
