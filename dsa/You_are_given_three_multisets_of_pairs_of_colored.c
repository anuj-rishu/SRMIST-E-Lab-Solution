#include <cstdio>
#include <algorithm>
using namespace std;
int dp[202][202][202], R[202], G[202], B[202], r, g, b, i, j, k;

void read(int *a, int n) {
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    sort(a + 1, a + n + 1);
}

int main() {
    scanf("%d%d%d", &r, &g, &b);
    read(R, r);
    read(G, g);
    read(B, b);
    for (i = r; i >= 0; i--)
        for (j = g; j >= 0; j--)
            for (k = 0; k <= b; k++) {
                int &x = dp[i][j][k];
                if (i < r && j < g)
                    x = max(x, dp[i + 1][j + 1][k] + R[r - i] * G[g - j]);
                if (i < r && k)
                    x = max(x, dp[i + 1][j][k - 1] + R[r - i] * B[k]);
                if (j < g && k)
                    x = max(x, dp[i][j + 1][k - 1] + G[g - j] * B[k]);
            }
    printf("%d", dp[0][0][b]);
}
