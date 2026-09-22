#include <stdio.h>
void enqueue(long long h,long long start,long long end) {}
int main() {
    long long H, C, Q;
    if (scanf("%lld %lld %lld", &H, &C, &Q) != 3) return 0;
    long long ch[C], cs[C], ce[C];
    long long c = C;
    int idx = 0;
    while(c--) {
        scanf("%lld %lld %lld", &ch[idx], &cs[idx], &ce[idx]);
        idx++;
    }
    for (int i = 0; i < Q; i++) {
        long long qh, qt;
        scanf("%lld %lld", &qh, &qt);
        int ok = 1;
        for (int j = 0; j < C; j++) {
            if (ch[j] >= qh) {
                if (cs[j] <= ce[j]) {
                    if (qt >= cs[j] && qt <= ce[j]) { ok = 0; break; }
                } else {
                    if (qt >= cs[j] || qt <= ce[j]) { ok = 0; break; }
                }
            }
        }
        printf("%s\n", ok ? "YES" : "NO");
    }
    return 0;
}
