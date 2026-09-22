#include <stdio.h>
#include <stdlib.h>

int **dp;
int *counter;

int solve(int idx, int rem, int sz) {
    if (idx == sz) return rem == 0;
    if (dp[idx][rem] != -1) return dp[idx][rem];
    long long ans = solve(idx + 1, rem, sz);
    if (rem > 0)
        ans = (ans + (long long)counter[idx] * solve(idx + 1, rem - 1, sz)) % 1000000007;
    return dp[idx][rem] = ans;
}

int main() {
    int n, k, i;
    scanf("%d%d", &n, &k);
    if (k > n) {
        printf("Invaild.\n");
        return 0;
    }
    int p_count[105] = {0};
    for (i = 2; i <= n; i++) {
        int p;
        scanf("%d", &p);
        p_count[p]++;
    }
    counter = (int *)malloc(105 * sizeof(int));
    int sz = 0;
    for (i = 1; i <= n; i++)
        if (p_count[i] > 0) counter[sz++] = p_count[i];
    counter[sz++] = 1;

    dp = (int **)malloc(sz * sizeof(int *));
    for (i = 0; i < sz; ++i) {
        dp[i] = (int *)malloc((k + 1) * sizeof(int));
        for (int j = 0; j <= k; j++) dp[i][j] = -1;
    }
    printf("%d\n", solve(0, k, sz));
}
