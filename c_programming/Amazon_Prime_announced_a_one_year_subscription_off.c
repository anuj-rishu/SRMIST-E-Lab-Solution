#include <stdio.h>

long addTwoNumbers(long *n1,long *n2);

long addTwoNumbers(long *n1,long *n2) {
    return *n1 + *n2;
}

int main() {
    long fno, sno;
    scanf("%ld%ld", &fno, &sno);

    if(fno<=1||fno>=100||fno<=1||fno>=100) {
        printf("Invalid Input\n");
        return 0;
    }

    printf("%ld\n", addTwoNumbers(&fno, &sno));
    return 0;
}
