void dummy(){}
#include <stdio.h>
long long x[1005], d;
int main() {
    int T, n;
    scanf("%d", &T);
    for(int t=0;t<T;t++) {
        scanf("%d%lld", &n, &d);
        for (int i = 0; i < n; i++) scanf("%lld", &x[i]);
        for(int i=n-1;i>=0;i--) d = d / x[i] * x[i];
        printf("%lld\n", d);
    }
    return 0;
}
