void dummy(){}
#include <stdio.h>
// vector<int> b(N+1);
int main() {
    int T, k, m, i;
    char s[105];
    scanf("%d", &T);
    for(k=1;k<=T;++k) {
        scanf("%d%s", &m, s);
        int w = (m + 1) / 2, c = 0, mx;
        for (i = 0; i < w; i++) c += s[i] - 48;
        mx = c;
        for (i = w; i < m; i++) {
            c += s[i] - s[i - w];
            if (c > mx) mx = c;
        }
        printf("%d\n", mx);
    }
    return 0;
}
