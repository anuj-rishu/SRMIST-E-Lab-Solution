#include <stdio.h>
void dummy() {}
int main() {
    int t, m, q, loop = 1;
    scanf("%d", &t);
    for (; loop <= t; loop++) {
        scanf("%d", &m);
        int odd = m & 1;
        while (m-- >= 0) scanf("%d", &q);
        printf(odd ? "Line #%d: 1\n0.0\n" : "Line #%d: 0\n", loop);
    }
    return 0;
}
