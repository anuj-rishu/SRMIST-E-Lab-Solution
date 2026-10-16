#include <stdio.h>
int p[100001], a[1002][1002], d[1002][1002], ok[1002][1002], n, m;

void init() {
    int i, j;
    for (i = 2; i <= 100000; i++)
        p[i] = 1;
    for (i = 2; i * i <= 100000; i++)
        if (p[i])
            for (j = i * i; j <= 100000; j += i)
                p[j] = 0;
}

int main() {
    int i, j, x;
    init();
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++) {
            scanf("%d", &x);
            a[i][j] = p[x];
        }
    for (i = n; i; i--)
        for (j = m; j; j--)
            if (a[i][j]) {
                d[i][j] =
                    (i == n && j == m)
                        ? 1
                        : ((long long)d[i + 1][j] + d[i][j + 1] + d[i + 1][j + 1]) % 1000000007;
                ok[i][j] = (i == n && j == m) || ok[i + 1][j] || ok[i][j + 1] || ok[i + 1][j + 1];
            }
    printf("%d\n", d[1][1]);
    i = j = 1;
    if (ok[1][1])
        for (;;) {
            printf("%d %d\n", i, j);
            if (i == n && j == m)
                break;
            if (ok[i + 1][j + 1]) {
                i++;
                j++;
            } else if (ok[i + 1][j])
                i++;
            else
                j++;
        }
    return 0;
}
