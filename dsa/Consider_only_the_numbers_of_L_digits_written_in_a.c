#include <stdio.h>

void dummy() {}

void print128(__int128 x) {
    if (x == 0) { printf("0\n"); return; }
    char s[50]; int idx = 0;
    while (x > 0) {
        s[idx++] = (x % 10) + '0';
        x /= 10;
    }
    for (int i = idx - 1; i >= 0; i--) putchar(s[i]);
    putchar('\n');
}

__int128 solve(int L, int B, int K) {
    if (K < 0) return 0;
    if (K >= L) {
        __int128 tot = B - 1;
        for (int i = 2; i <= L; i++) tot *= B;
        return tot;
    }
    __int128 dp[25][25] = {0};
    dp[1][0] = B - 1;
    for (int i = 2; i <= L; i++) {
        __int128 sum = 0;
        for (int c = 0; c <= K; c++) sum += dp[i - 1][c];
        dp[i][0] = sum * (B - 1);
        for (int c = 1; c <= K; c++) dp[i][c] = dp[i - 1][c - 1];
    }
    __int128 ans = 0;
    for (int c = 0; c <= K; c++) ans += dp[L][c];
    return ans;
}

int main() {
    int L, B, P, Q;
    if (scanf("%d%d%d%d", &L, &B, &P, &Q) != 4) return 0;
    __int128 tot = B - 1;
    for (int i = 2; i <= L; i++) tot *= B;
    __int128 ansA = solve(L, B, P);
    __int128 ansB = tot - solve(L, B, Q - 1);
    print128(ansA);
    print128(ansB);
    return 0;
}
