#include <stdio.h>

int a[100005];
int n, k;

int check(int mid) {
    int i = 0;
    int jumps = 0;
    while(i < n) {
        if (i == n - 1) break;
        int next = -1;
        for (int j = i + 1; j < n; j++) {
            if (a[j] > a[i] && a[j] - a[i] <= mid) {
                next = j;
            }
        }
        if (next == -1) return 0;
        i = next;
        jumps++;
    }
    return jumps <= k;
}

void solve() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    int low = 1, high = 1000000000, ans = high;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    printf("%d\n", ans);
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        solve();
    }
    return 0;
}
