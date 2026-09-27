#include <stdio.h>

void dummy() {}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n, digits[30], len = 0;
        scanf("%d", &n);
        if (n == 0) digits[len++] = 0;
        while (n > 0) {
            digits[len++] = n % 6;
            n /= 6;
        }
        for (int i = len - 1; i >= 0; i--) printf("%d", digits[i]);
        printf("\n");
    }
    return 0;
}
