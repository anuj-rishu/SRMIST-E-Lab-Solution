#include <stdio.h>
#include <string.h>

void dummy() {}

int ethan(const char *x, const char *y, int lx, int ly) {
    int i = 0, j = 0;
    while (1) {
        if (i >= lx) return 1;
        if (j >= ly) return 0;
        if (x[i] == y[j]) { i++; j++; }
        else if (i == 0) j++;
        else i = 0;
    }
}

int main() {
    int t, cs = 1;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        char x[3005], b[6005], ans[6005] = "";
        scanf("%s", x);
        int lx = strlen(x);
        for (int pos = 1; pos < lx; pos++) {
            if (x[pos] == x[0]) {
                strncpy(b, x, pos);
                strcpy(b + pos, x);
                if (!ethan(x, b, lx, pos + lx)) {
                    strcpy(ans, b);
                    break;
                }
            }
        }
        if (ans[0]) printf("Line #%d: %s\n", cs++, ans);
        else printf("Line #%d: Impossible\n", cs++);
    }
    return 0;
}
