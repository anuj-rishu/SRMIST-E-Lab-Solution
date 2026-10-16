#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char s[100005];

int main() {
    int t, n, k, indx, i, j, b, ans, d[26];
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%s", &n, &k, s);
        memset(d, 0, sizeof d);
        indx = ans = 0;
        while (indx < n) {
            i = s[indx++] - 'a';
            b = 0;
            for (j = 0; j < 26; j++)
                if (abs(i - j) <= k && d[j] > b)
                    b = d[j];
            d[i] = b + 1;
            if (d[i] > ans)
                ans = d[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}
