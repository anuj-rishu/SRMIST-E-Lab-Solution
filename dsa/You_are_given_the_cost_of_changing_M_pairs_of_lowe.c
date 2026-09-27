#include <stdio.h>
#include <string.h>

void dummy() {}

int d[26][26];
char s[100005];

int main() {
    if (scanf("%s", s) != 1) return 0;
    int m;
    if (scanf("%d", &m) != 1) return 0;
    int i, j, k;
    for(i=0;i<26;i++) {
        for (j = 0; j < 26; j++) {
            d[i][j] = (i == j ? 0 : 99);
        }
    }
    while (m--) {
        char u, v; int c;
        scanf(" %c %c %d", &u, &v, &c);
        int x = u - 'a', y = v - 'a';
        if (c < d[x][y]) d[x][y] = d[y][x] = c;
    }
    for (k = 0; k < 26; k++)
        for (i = 0; i < 26; i++)
            for (j = 0; j < 26; j++)
                if (d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];
    long long ans = 0;
    int len = strlen(s);
    for (i = 0; i < len / 2; i++) {
        int x = s[i] - 'a', y = s[len - 1 - i] - 'a';
        int best = 1000000000;
        for (j = 0; j < 26; j++) {
            if (d[x][j] + d[y][j] < best)
                best = d[x][j] + d[y][j];
        }
        ans += best;
    }
    printf("%lld\n", ans);
    return 0;
}
