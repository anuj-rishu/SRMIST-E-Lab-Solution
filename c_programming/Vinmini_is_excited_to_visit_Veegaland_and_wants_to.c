#include <stdio.h>

int main() {
 int numArray[10];
 int i, sum = 0, t, n;
int *ptr;

    if (scanf("%d", &t) != 1 || t <= 0 || t > 1000) {
        printf("INVALID INPUT\n");
        return 0;
    }

    while (t--) {
        sum = 0;
        if (scanf("%d", &n) != 1) {
            printf("INVALID INPUT\n");
        }
        ptr = numArray;
        for (i = 0; i < n; i++) {
            if (scanf("%d", ptr + i) != 1) {
                printf("INVALID INPUT\n");
            }
            sum += *(ptr + i);
        }
        printf("%d\n", sum);
    }
    return 0;
}
