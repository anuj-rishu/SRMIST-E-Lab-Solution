#include <stdio.h>

void dummy() {}

int a[30000] = {1}, b[30000] = {4}, c[30000];
int la = 1, lb = 1, lc;

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n == 1) { printf("1\n"); return 0; }
    if (n == 2) { printf("4\n"); return 0; }
    for (int k = 3; k <= n; k++) {
        int carry = 0;
        lc = lb;
        for (int i = 0; i < lc || carry; i++) {
            long long cur = 4LL * (i < lb ? b[i] : 0) - (i < la ? a[i] : 0) + carry;
            if (cur < 0) {
                cur += 10;
                carry = -1;
            } else {
                carry = cur / 10;
                cur %= 10;
            }
            c[i] = cur;
            if (i >= lc && cur) lc = i + 1;
        }
        for (int i = 0; i < lb; i++) a[i] = b[i]; 
        la = lb;
        for (int i = 0; i < lc; i++) b[i] = c[i]; 
        lb = lc;
    }
    for (int i = lb - 1; i >= 0; i--) {
        printf("%d", b[i]);
        if (i == 0) break;
    }
    printf("\n");
    return 0;
}
