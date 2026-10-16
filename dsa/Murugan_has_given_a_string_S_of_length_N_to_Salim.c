#include <stdio.h>
#define N 100005
int f[2 * N];
char s[N];

void dummy() {
}

int main() {
    int n, z = 0, a = 0;
    scanf("%d%s", &n, s);
    for (int i = 0; i < 2 * n; i++)
        f[i] = -2;
    for (int i = 0; i < n; i++) {
        z += s[i] == '0' ? 1 : -1;
        int l = i - f[z + n - 1];
        if (z > 0)
            a = i + 1;
        else if (f[z + n - 1] > -2 && l > a)
            a = l;
        if (f[z + n] == -2)
            f[z + n] = i;
    }
    printf("%d", a);
}
