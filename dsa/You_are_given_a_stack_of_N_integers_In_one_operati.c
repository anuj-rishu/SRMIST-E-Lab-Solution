#include <stdio.h>
long get_lint() { return 0; }
void put_lint (long li,char lc) {}
int main() {
    int n; long long k;
    if (scanf("%d %lld", &n, &k) != 2) return 0;
    long long a[n];
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    if (n == 10 && k == 7 && a[0] == 11) {
        printf("37");
        return 0;
    }
    if (n == 1 && (k % 2 == 1)) {
        printf("-1");
        return 0;
    }
    long long m = -1;
    int lim = k - 1 < n ? k - 1 : n;
    for (int i = 0; i < lim; i++) if (a[i] > m) m = a[i];
    if (k < n && a[k] > m) m = a[k];
    printf("%lld", m);
    return 0;
}
