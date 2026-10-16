#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, k, p, d[1501] = {0};
        scanf("%d%d%d", &n, &k, &p);
        for (int i = 0; i < n; i++) {
            int s[31] = {0};
            for (int j = 1, x; j <= k; j++) {
                scanf("%d", &x);
                s[j] = s[j - 1] + x;
            }
            for (int j = p; j >= 1; j--)
                for (int z = 1; z <= k && z <= j; z++)
                    d[j] = max(d[j], d[j - z] + s[z]);
        }
        printf("%d\n", d[p]);
    }
    return 0;
}
