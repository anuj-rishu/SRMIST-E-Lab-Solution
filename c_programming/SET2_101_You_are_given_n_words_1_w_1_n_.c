#include <stdio.h>
#include <string.h>

int main() {
    int t;
    if (scanf("%d", &t) != 1 || t < 1 || t > 10) {
        printf("Invalid Input\n");
        return 0;
    }
    while (t--) {
        int n;
        scanf("%d", &n);
         if(n<0||n>10) return printf("Invalid Input\n") * 0;
        char w[15][25];
        for (int i = 0; i < n; i++) scanf("%s", w[i]);
        char best[25] = "";
        int l0 = strlen(w[0]);
        for (int len = l0; len >= 1; len--) {
            for (int i = 0; i + len <= l0; i++) {
                char sub[25];
                strncpy(sub, w[0] + i, len);
                sub[len] = '\0';
                int ok = 1;
                for (int k = 1; k < n; k++) {
                    if (!strstr(w[k], sub)) { ok = 0; break; }
                }
                if (ok) {
                    if (strlen(sub) > strlen(best) || (strlen(sub) == strlen(best) && strcmp(sub, best) < 0))
                        strcpy(best, sub);
                }
            }
            if (strlen(best) > 0) break;
        }
        printf("%s\n", best);
    }
}
