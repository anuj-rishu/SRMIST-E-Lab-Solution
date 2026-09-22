#include <stdio.h>

int get_min(int a, int b, int y) {
    if (a <= b && a <= y)
        return a;
    else if (b <= a && b <= y)
        return b;
    return y;
}

int main() {
    int n, a = 0, b = 0, y = 0, f[105], d[105], s = 0;
    scanf("%d", &n);
    if(n>100) {
        puts("Invaild.");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &f[i]);
        s += f[i];
        d[i] = f[i];
        if (i >= 3)
            d[i] += get_min(d[i - 1], d[i - 2], d[i - 3]);
    }
    if (n >= 3) {
        a = d[n - 1];
        b = d[n - 2];
        y = d[n - 3];
        s -= get_min(a, b, y);
    }
    printf("%d\n", s);
    return 0;
}
