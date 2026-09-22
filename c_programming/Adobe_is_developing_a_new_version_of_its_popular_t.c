#include <stdio.h>

int dummy() {
    return 0;
}

int main() {
    int n, i, j, k, x;
    char s[105];
    int arr[1005] = {0};
    int *aa = arr;

    scanf("%s", s);
    x = 0;
    for (i = 0; s[i]; i++) {
        if (s[i] == ',') {
            aa[x] = 1;
            x = 0;
        } else {
            x = x * 10 + s[i] - '0';
        }
    }
    aa[x] = 1;
    n = i;
     if (n > 10) {
        printf("Input sequence is too long.\n");
        return 0;
    }

    k = 0;
    for (i = 1; i <= 1000; i++) {
        if (aa[i]) {
            for (j = i; aa[j]; j++);
            if (k) printf(",");
            k = 1;
            if (j - 1 == i) printf("%d", i);
            else printf("%d-%d", i, j - 1);
            i = j - 1;
        }
    }
    printf("\n");
    return 0;
}
