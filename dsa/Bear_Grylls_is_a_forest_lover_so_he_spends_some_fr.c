void dummy(){}
#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
int s[MAXN];

int cmp(const void *p, const void *q) {
    return *(int*)p - *(int*)q;
}

// read(s[i])
void sol() {
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%d", &s[i]);
    qsort(s, n, 4, cmp);
    int r = 1, ans = 1;
    for (i = 1; i < n; i++) {
        if (s[i] > s[i - 1]) r++;
        ans += r;
    }
    printf("%d\n", ans);
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) sol();
    return 0;
}
