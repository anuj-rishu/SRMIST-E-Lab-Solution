#include <stdio.h>
int scount[100][100], colours[100], s[101];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        s[0] = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", colours + i);
            s[i + 1] = s[i] + colours[i];
            scount[i][i] = 0;
        }
        for (int len = 2; len <= n; len++)
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                scount[i][j] = 2147483647;
                for (int k = i; k < j; k++) {
                    int a = i == k ? colours[i] : (s[k + 1] - s[i]) % 100,
                        b = k + 1 == j ? colours[j] : (s[j + 1] - s[k + 1]) % 100;
                    int z = scount[i][k] + scount[k + 1][j] + a * b;
                    if (z < scount[i][j])
                        scount[i][j] = z;
                }
            }
        printf("%d\n", scount[0][n - 1]);
    }
    return 0;
}
