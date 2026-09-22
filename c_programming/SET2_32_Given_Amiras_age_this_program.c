#include <stdio.h>

int main() {
    int age;
    scanf("%d", &age);
    if (age <= 1 || age >= 100) {
        printf("Invalid input\n");
    } else if (age >= 18) {
        printf("Eligible\n");
    } else {
        printf("Not Eligible\n");
    }
    return 0;
}
