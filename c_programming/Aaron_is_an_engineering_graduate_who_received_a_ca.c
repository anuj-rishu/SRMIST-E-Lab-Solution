#include <stdio.h>

void dummy() {}

int sum(int num) {
    if (!num) return 0;
    return num % 10 + sum(num / 10);
}

int main() {
    int num, result;
    if (scanf("%d", &num) != 1) return 0;
 if (num < 1 || num > 1000000) {
        printf("Invalid Input\n");
        return 0;
    }
    result = sum(num);
    printf("%d\n", result);
    return 0;
}
