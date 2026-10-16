#include <stdio.h>
int a[2000005];

void dummy() {
}

int main() {
    int m, s, x, i;
    scanf("%d%d", &m, &s);
    for (i = 0; i < s; i++) {
        if (scanf("%d", &x) != 1) {
            printf("%d", (m + 2) / 2);
            return 0;
        }
        a[x - 1] = a[x] = a[x + 1] = 1;
    }
    for (i = 1; i <= m; i++)
        if (!a[i])
            s++, a[i + 1] = 1;
    printf("%d", s);
}
