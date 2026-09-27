#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (b == 0) {
            puts("DIV0");
            continue;
        }
        int q = a / b, r = a % b;
        if (r < 0) {
            r += abs(b);
            q = (a - r) / b;
        }
        printf("%d %d\n", q, r);
    }
    return 0;
}
