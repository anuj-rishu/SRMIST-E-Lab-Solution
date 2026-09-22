#include <stdio.h>

int main() {
    int x, y;
    int *xptr, *yptr;

    if (scanf("%d", &x) != 1 || x < 1 || x > 100)
        printf("INVALID INPUT\n");

    if (scanf("%d", &y) != 1 || y < 1 || y > 100)
        printf("INVALID INPUT\n");

    xptr = &x;
 yptr = &y;

    if (*xptr > *yptr)
        printf("%d\n", *xptr);
    else
        printf("%d\n", *yptr);

    return 0;
}
