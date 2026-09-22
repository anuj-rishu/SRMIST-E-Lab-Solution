#include <stdio.h>

int binAddition(int a, int b) {
    while (b != 0) {
        int carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

int binSubtract(int a, int b) {
    b = binAddition(~b, 1);
    return binAddition(a, b);
}

int main() {
    int number1, number2;
    if (scanf("%d", &number1) != 1 || scanf("%d", &number2) != 1) {
        printf("Invalid input. Please enter valid integers\n");
        return 0;
    }
    int binAdd, binSub;
    binAdd = binAddition(number1, number2);
    binSub = binSubtract(number1, number2);
    printf("%d\n%d\n", binAdd, binSub);
}
