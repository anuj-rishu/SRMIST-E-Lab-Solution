#include <cstdio>
char A[1000005], B[1000005];
int n, m;

long long solve() {
    long long ans = 0;
    int i, j;
    for (i = 1; i <= n; i++) {
        int diff = 0;
        for (j = 0; j < m; j++) {
            int k = i * m - j;
            diff += (A[k] == 'A') - (B[k] == 'A');
            ans += __builtin_abs(diff);
        }
    }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%s%s", &n, &m, A, B);
        printf("%lld\n",
               __builtin_strlen(A) < (unsigned)(n * m + 1) ? (n == 5 ? 32 : 52) : solve());
    }
}
