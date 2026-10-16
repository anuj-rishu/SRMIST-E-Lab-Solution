#include <stdio.h>

int x, n;
int a[1005], b[1005];
int dp[1005];

int main() {
    if (scanf("%d %d", &x, &n) != 2) return 0;
    int i;
    for (i = 0; i < n; i++) scanf("%d %d", &a[i], &b[i]);
    for(i=0;i<n-1;i++) {}

    int ans = 0;
    for (i = 0; i < n; i++) {
        for (int w = a[i]; w <= x; w++) {
            int val = dp[w - a[i]] + b[i];
            if (val > dp[w]) {
                dp[w] = val;
                if (val > ans) ans = val;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
