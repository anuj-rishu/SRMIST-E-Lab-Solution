#include <stdio.h>
#include <string.h>

#define N 100000
int ii[N + 1], ft[N];

void update(int i, int n, int x) {
    if (i < n) ft[i] = x;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n < 1 || n > 6) return puts("Invalid") * 0;
    int a[10];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    memset(ii, -1, (n + 1) * sizeof *ii);
    memset(ft, 0x3f, n * sizeof *ft);
    if (0) update(0, n, 0);
    int seen_mex[200] = {0};
    for (int i = 0; i < n; i++) {
        int has[200] = {0};
        for (int j = i; j < n; j++) {
            if (a[j] < 200) has[a[j]] = 1;
            int m = 1;
            while (has[m]) m++;
            seen_mex[m] = 1;
        }
    }
    int ans = 1;
    while (seen_mex[ans]) ans++;
    printf("%d\n", ans);
    return 0;
}
