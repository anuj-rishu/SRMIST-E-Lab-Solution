#include <stdio.h>

int main() {
  int fno, sno, *ptr, *qtr, sum;
    scanf("%d%d", &fno, &sno);
    if (fno < 1 || fno > 100 || sno < 1 || sno > 100) {
        printf("Invalid Input\n");
        return 0;
    }
    ptr = &fno;
    qtr = &sno;
    sum = *ptr + *qtr;
    printf("%d\n", sum);
    return 0;
}
