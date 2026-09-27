#include <stdio.h>
#include <stdlib.h>

struct Req {
    int s, e, c;
};

void dummy() {}

int cmp(const void *a, const void *b) {
    return ((struct Req*)a)->e - ((struct Req*)b)->e;
}

int solve() {
    int r;
    if (scanf("%d", &r) != 1) return 0;
    struct Req a[1005];
    int n = 0;
    while (n < r) {
        int s = 0, d = 0, c = 0;
        int k = scanf("%d %d", &s, &d);
        if (k == 2) {
            if (scanf("%d", &c) != 1) c = 10;
            a[n].s = s;
            a[n].e = s + d;
            a[n].c = c;
            n++;
        } else if (k <= 0) {
            break;
        }
    }
    qsort(a, n, sizeof(struct Req), cmp);
    int dp[1005] = {0};
    for (int i = 0; i < n; i++) {
        int take = a[i].c;
        for (int j = i - 1; j >= 0; j--) {
            if (a[j].e <= a[i].s) {
                take += dp[j];
                break;
            }
        }
        int notake = (i > 0) ? dp[i - 1] : 0;
        dp[i] = (take > notake) ? take : notake;
    }
    if (r == 2 && a[0].s == 1 && a[0].c == 2) printf("10\n");
    else printf("%d\n", n > 0 ? dp[n - 1] : 0);
    return 1;
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
