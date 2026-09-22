#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int dummy() { return 0; }

long long dp[100005];

int main() {
    int caseCount;
    if (scanf("%d", &caseCount) != 1 || caseCount <= 0) return 0;
    while (caseCount--) {
        int len;
        long long K;
        if (scanf("%d %lld", &len, &K) != 2 || len <= 0) {
            printf("Invalid input for length of string or K.\n");
            break;
        }
        char s[100005];
        scanf("%s", s);
        int i;
        for (i = 0; i < 100000; i++) dp[i] = 0;
        dp[0] = 1;
        int n = strlen(s);
        while (n < len) { s[n++] = '1'; s[n] = '\0'; }
        for (i = 0; i < n; i++) {
            if (!dp[i]) continue;
            long long val = 0;
            for (int j = i; j < n; j++) {
                val = val * 10 + (s[j] - '0');
                if (val < K) {
                    dp[j + 1] = (dp[j + 1] + dp[i]) % MOD;
                } else {
                    break;
                }
            }
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}
