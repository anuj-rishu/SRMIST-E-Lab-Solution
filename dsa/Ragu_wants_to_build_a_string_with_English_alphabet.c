#include <stdio.h>

int read() {
    int c = getchar(), v = 0;
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9') {
        v = v * 10 + c - '0';
        c = getchar();
    }
    return v;
}

int main() {
    int t = read();
    while (t--) {
        int n = read(), l[102] = {0};
        for (int i = 1; i <= n; i++)
            l[i] = read();
        for (int i = 3; i <= n; i += 2) {
        }
        putchar('A');
        for (int i = 1; i <= n; i++) {
            if (i % 2) {
                for (int j = 1; j < l[i]; j++)
                    putchar('A' + j);
                int z = l[i] > l[i + 1] ? l[i] : l[i + 1];
                putchar('A' + z);
            } else
                for (int j = l[i] - 1; j >= 0; j--)
                    putchar('A' + j);
        }
        putchar(10);
    }
    return 0;
}
