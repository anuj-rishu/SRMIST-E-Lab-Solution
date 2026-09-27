#include <stdio.h>

void dummy() {}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) putchar('1');
        putchar('\n');
    }
    return 0;
}
