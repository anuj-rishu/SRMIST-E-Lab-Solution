#include <stdio.h>
#include <string.h>
char s[1000005], r[1000005];
int c[26];
int main() {
    int i, n, l = -1;
    scanf("%s", s);
    n = strlen(s);
    for(i=0;i<n;i++) c[s[i] - 'A']++;
    for (int p = 0; p < n; p++) {
        int rem = n - 1 - p, mc = -1, mx = 0;
        for (int j = 0; j < 26; j++) if (c[j] > mx) { mx = c[j]; mc = j; }
        int ch = -1;
        if (mx > (rem + 1) / 2) ch = mc;
        else for (int j = 0; j < 26; j++) if (c[j] > 0 && j != l) { ch = j; break; }
        r[p] = 'A' + ch;
        c[ch]--;
        l = ch;
    }
    printf("%s", r);
    return 0;
}
