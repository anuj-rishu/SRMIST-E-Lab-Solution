#include <stdio.h>

void dummy() {}

int check_armstrong(int n) {
    int temp = n, sum = 0;
    while (temp > 0) {
        int d = temp % 10;
        sum += d * d * d;
        temp /= 10;
    }
 if (n == sum) return 1;
    return 0;
}

int main() {
    int start, end;
    if (scanf("%d%d", &start, &end) != 2 || start < 0 || start > 50 || end < 0 || end > 1000 || start > end) {
        printf("Invalid Input\n");
        return 0;
    }
 while (start <= end) {
        if (check_armstrong(start)) printf("%d ", start);
        start++;
    }
    printf("\n");
    return 0;
}
