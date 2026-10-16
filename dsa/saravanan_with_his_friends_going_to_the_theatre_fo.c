#include <stdio.h>

int main() {
    int N, i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; i++) {
        for (j = 1; j <= i; j++)
            printf("%d ", 2 * j - (i % 2));
        if (i < N)
            puts("");
    }
    return 0;
}
