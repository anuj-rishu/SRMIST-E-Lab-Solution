#include <stdio.h>

void dummy() {}

int main() {
    int t, cs = 1;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int b, a, k, p, q, x1, y1, x2 = 0, y2 = 0;
        scanf("%d%d%d%d%d%d%d", &b, &a, &k, &p, &q, &x1, &y1);
        if (k == 2) scanf("%d%d", &x2, &y2);
        int sp = (p + q) & 1;
        int a1 = (x1 + y1) & 1;
        int a2 = (x2 + y2) & 1;
        if (k == 2 && sp == a1 && sp == a2) printf("Line #%d: Y\n", cs++);
        else printf("Line #%d: N\n", cs++);
    }
    return 0;
}
