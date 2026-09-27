#include <stdio.h>

void dummy() {}

long long V[10005], A[10005], B[10005];

int main() {
    int t, cs = 1;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int h, k;
        scanf("%d%d", &h, &k);
        for (int i = 0; i < k; i++) scanf("%lld", &V[i]);
        long long pv, qv, rv, sv;
        scanf("%lld%lld%lld%lld", &pv, &qv, &rv, &sv);
        for (int i = 0; i < k; i++) scanf("%lld", &A[i]);
        long long pa, qa, ra, sa;
        scanf("%lld%lld%lld%lld", &pa, &qa, &ra, &sa);
        for (int i = 0; i < k; i++) scanf("%lld", &B[i]);
        long long pb, qb, rb, sb;
        scanf("%lld%lld%lld%lld", &pb, &qb, &rb, &sb);

        for (int i = k; i < h; i++) {
            V[i] = (pv * V[i - 2] + qv * V[i - 1] + rv) % sv;
            A[i] = (pa * A[i - 2] + qa * A[i - 1] + ra) % sa;
            B[i] = (pb * B[i - 2] + qb * B[i - 1] + rb) % sb;
        }

        long long sumV = 0, sumA = 0, sumAB = 0;
        long long sur = 0, def = 0;
        for (int i = 0; i < h; i++) {
            sumV += V[i];
            sumA += A[i];
            sumAB += A[i] + B[i];
            if (V[i] > A[i] + B[i]) sur += V[i] - (A[i] + B[i]);
            if (V[i] < A[i]) def += A[i] - V[i];
        }

        if (sumV < sumA || sumV > sumAB) {
            printf("Line #%d: -1\n", cs++);
        } else {
            long long ans = sur > def ? sur : def;
            printf("Line #%d: %lld\n", cs++, ans);
        }
    }
    return 0;
}
