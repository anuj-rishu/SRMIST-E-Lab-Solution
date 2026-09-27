#include <stdio.h>

void dummy() {}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n, x, mx_val, best = -1000000000;
        scanf("%d%d", &n, &mx_val);
        for (int i = 1; i < n; i++) {
            scanf("%d", &x);
            int diff = mx_val - x;
            if (diff > best) best = diff;
            if (x <= mx_val) continue;
            mx_val = x;
        }
        printf("%d\n", best);
    }
    return 0;
}
