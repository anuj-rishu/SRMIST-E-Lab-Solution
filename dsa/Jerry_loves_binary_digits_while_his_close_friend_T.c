#include <stdio.h>
int s[502][502];

int maxi(int a, int b) {
    return a > b ? a : b;
}

int mini(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, m, i, j, k, x, total = 0, best = -1;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++) {
            scanf("%d", &x);
            total += x;
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + 1 - 2 * x;
        }
    for (k = 1; k <= mini(n, m); k++)
        for (i = k; i <= n; i++)
            for (j = k; j <= m; j++)
                best = maxi(best, s[i][j] - s[i - k][j] - s[i][j - k] + s[i - k][j - k]);
    printf("%d", total + best);
    return 0;
}
