#include <stdio.h>

void dummy() {}

int main() {
    int c, p, t;
    while (scanf("%d%d%d", &c, &p, &t) == 3) {
        if (p + t <= c) printf("%d\n", p + t);
        else printf("%d\n", 2 * c - p - t);
    }
    return 0;
}
