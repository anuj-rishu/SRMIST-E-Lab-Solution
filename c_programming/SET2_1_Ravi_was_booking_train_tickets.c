#include <stdio.h>

int main() {
    int num1,num2,num3;
    int sum;

    scanf("%d %d %d", &num1, &num2, &num3);

    if (num1 < 1 || num1 > 15 || num2 < 1 || num2 > 15 || num3 < 1 || num3 > 15) {
        printf("Invalid Inputs");
    } 
    else {
        sum = num1 + num2 + num3;
        printf("%d", sum);
    }

    return 0;
}