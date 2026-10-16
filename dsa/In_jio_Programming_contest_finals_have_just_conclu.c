#include <stdio.h>
char a[405][405];
int n, m;

void dummy() {
}

int solve() {
    for (int w = 1; w < n; w++) {
        int good[405] = {0}, have = 0;
        for (int i = 1; i < n; i++)
            if (i != w) {
                for (int j = 0; j < m; j++)
                    good[i] |= a[0][j] == 'Y' && a[w][j] == 'Y' && a[i][j] != 'Y';
            }
        for (int j = 0; j < m; j++)
            if (a[0][j] != 'Y' && a[w][j] == 'Y') {
                int ok = 1;
                for (int i = 1; i < n; i++)
                    if (i != w && !good[i]) {
                        int lose = 0;
                        for (int k = 0; k < m; k++)
                            lose |= a[0][k] == 'Y' && a[w][k] != 'Y' && a[i][k] != 'Y';
                        ok &= a[i][j] != 'Y' && lose;
                    }
                have |= ok;
            }
        if (have)
            return 1;
    }
    return 0;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        scanf("%d%d", &n, &m);
        int i;
        for (i = 0; i < n; ++i)
            scanf("%s", a[i]);
        for (i = 1; i < n; ++i) {
        }
        printf("Line #%d: %c\n", c, solve() ? 'Y' : 'N');
    }
}
