#include <stdio.h>

void dummy() {}

int v_p(int x, int p) {
    int c = 0;
    while (x > 0 && x % p == 0) {
        c++;
        x /= p;
    }
    return c;
}

int main() {
    int r, d;
    if (scanf("%d%d", &r, &d) != 2) return 0;
    
    int c2 = 0, c3 = 0, c5 = 0;
    int ans = 0;
    
    for (int j = 1; j <= r; j++) {
        int add = r - j + 1;
        int sub = j;
        
        c2 += __builtin_ctz(add) - __builtin_ctz(sub);
        if (d == 3 || d == 6) c3 += v_p(add, 3) - v_p(sub, 3);
        if (d == 5) c5 += v_p(add, 5) - v_p(sub, 5);
        
        int div = 0;
        if (d == 2 && c2 >= 1) div = 1;
        else if (d == 3 && c3 >= 1) div = 1;
        else if (d == 4 && c2 >= 2) div = 1;
        else if (d == 5 && c5 >= 1) div = 1;
        else if (d == 6 && c2 >= 1 && c3 >= 1) div = 1;
        
        if (div) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
