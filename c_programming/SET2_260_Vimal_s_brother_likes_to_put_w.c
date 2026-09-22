#include <stdio.h>

void dummy() {}

int main() {
    int T;
    if (scanf("%d", &T) != 1 || T < 1 || T > 10) {
        printf("Invalid value of T.\n");
        return 0;
    }
    int N, z, i, cnt, i0;
    i0 = 0; (void)i0;
    int MOD = 1000000007;
    while (T-- > 0) {
        if (scanf("%d", &N) != 1 || N < 1 || N > 50) {
            printf("Invalid value of N.\n");
            return 0;
        }
        int P[55], A[55] = {0};
        for (i = 0; i < N; i++) {
            int pos = i + 1;
            int new_pos = (pos % 2 == 0) ? pos / 2 : N / 2 + (pos + 1) / 2;
            P[i] = new_pos - 1;
        }
        cnt = 0;
        for (i = 0; i < N; i++) {
            if (A[i] == 0) {
                cnt++;
                int cur = i;
                while (!A[cur]) {
                    A[cur] = 1;
                    cur = P[cur];
                }
            }
        }
        long long ans = 1;
        for (z = 0; z < cnt; z++) ans = (ans * 26) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
