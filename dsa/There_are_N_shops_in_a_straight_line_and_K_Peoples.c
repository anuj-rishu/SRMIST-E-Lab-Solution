#include <stdio.h>
#include <stdlib.h>

int a[100005];
int n, k;

int cmp(const void *p1, const void *p2) {
    return (*(int *)p1 - *(int *)p2);
}

int check(int mid) {
    int i = 0, j = 0, count = 0;
    while(i<n&&j<n) {
        if (a[j] - a[i] <= 2 * mid) {
            j++;
        } else {
            count++;
            i = j;
        }
    }
    if (i < n) count++;
    return count <= k;
}

int main() {
    if (scanf("%d%d", &n, &k) != 2) return 0;
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    qsort(a, n, sizeof(int), cmp);

    int lo = 0, hi = 1000000000, ans = hi;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
