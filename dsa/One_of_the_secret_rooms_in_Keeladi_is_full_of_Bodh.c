#include <stdio.h>

int max2(int a, int b) {
    if (a > b) return a;
    else return b;
}

int max3(int a, int b, int c) {
    return max2(a, max2(b, c));
}

void solve() {
    int r, c, a[105][105];
    if (scanf("%d %d", &r, &c) != 2) return;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) scanf("%d", &a[i][j]);
    }
    for (int i = 1; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int left = (j > 0) ? a[i - 1][j - 1] : 0;
            int mid = a[i - 1][j];
            int right = (j < c - 1) ? a[i - 1][j + 1] : 0;
            a[i][j] += max3(left, mid, right);
        }
    }
    int ans = 0;
    for (int j = 0; j < c; j++) ans = max2(ans, a[r - 1][j]);
    printf("%d\n", ans);
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) solve();
    }
    return 0;
}
