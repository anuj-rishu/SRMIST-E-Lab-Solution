#include <stdio.h>
#include <stdlib.h>

void compute(int *n, int a, int b, int **ans, int *last) {
    (void)ans; (void)last;
    if (a > b) { int tmp = a; a = b; b = tmp; }
    int num = *n;
    if (a == b) {
        printf("%d \n", (num - 1) * a);
        return;
    }
    for (int i = 0; i < num; i++) {
        int val = (num - 1 - i) * a + i * b;
        printf("%d ", val);
    }
    printf("\n");
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    if (t <= 0) {
        printf("Invalid Input\n");
        return 0;
    }
    int *n, **ans = NULL, *last = NULL;
    while (t--) {
        int num, a, b;
        scanf("%d%d%d", &num, &a, &b);
        n = &num;
        compute(n, a, b, ans, last);
    }
    return 0;
}
