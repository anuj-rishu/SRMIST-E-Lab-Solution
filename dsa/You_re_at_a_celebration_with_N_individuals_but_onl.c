#include <stdio.h>

int a[1000][1000];

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n;
        if (scanf("%d", &n) != 1) break;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        int c = 0;
        for (int i = 1; i < n; i++) {
            if (a[c][i] == 1) c = i;
        }
        int ok = 1;
        for (int i = 0; i < n; i++) {
            if (i != c) {
                if (a[c][i] == 1 || a[i][c] == 0) {
                    ok = 0;
                    break;
                }
            }
        }
        if (ok) printf("%d\n", c + 1);
        else printf("-1\n");
    }
    return 0;
}
