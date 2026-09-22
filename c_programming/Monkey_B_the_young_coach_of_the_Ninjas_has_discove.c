#include <stdio.h>

int get_min(int a, int b) {
    if (a < b) return a;
    return b;
}

int main() {
     int n, i, j, k, x, ans;
    int kk[128] = {0}, c;
    char s[105];

    if (scanf("%d%s", &n, s) < 2 || n > 10) {
        printf("Invaild.\n");
        return 0;
    }

    k = 0;
    for (i = 0; i < n; i++) {
        c = s[i];
        if (!kk[c]++) k++;
    }

    for (i = 0; i < 128; i++) kk[i] = 0;

    ans = n;
    x = 0;
    for (i = j = 0; i < n; i++) {
        while (j < n && x < k) {
            c = s[j++];
            if (!kk[c]++) x++;
        }
        if (x == k && j - i < ans)
            ans = j - i;
        c = s[i];
        if (!--kk[c]) x--;
    }

    printf("%d\n", ans);
    return 0;
}
