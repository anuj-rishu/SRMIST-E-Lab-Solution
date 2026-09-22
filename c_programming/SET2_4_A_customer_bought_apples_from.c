#include <stdio.h>

int main() {
    int billamt, amtgiven;
    scanf("%d", &amtgiven);
    scanf("%d", &billamt);
    if (billamt == 0) {
        printf("Error: Division by zero.\n");
    } else {
        printf("Quotient: %d\n", amtgiven / billamt);
        printf("Remainder: %d\n", amtgiven % billamt);
    }
    return 0;
}
