#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        int no[100],fs[100];
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &fs[i]);
        scanf("%d", &m);
        for (int i = 0; i < m; i++) scanf("%d", &no[i]);
        int ok = 1;
        for (int i = 0; i < m; i++) {
            int found = 0;
            for (int j = 0; j < n; j++) {
                if (no[i] == fs[j]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                ok = 0;
                break;
            }
        }
        if (ok) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
