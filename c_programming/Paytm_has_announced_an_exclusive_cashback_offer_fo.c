#include <stdio.h>

int main() {
    int currency;
    scanf("%d", &currency);
    if (currency >= 2000 || currency <= 1600)
        printf("Invalid input.\n");
    else
        (currency % 2 == 0) ? printf("Even Currency\n") : printf("Odd Currency\n");
}
