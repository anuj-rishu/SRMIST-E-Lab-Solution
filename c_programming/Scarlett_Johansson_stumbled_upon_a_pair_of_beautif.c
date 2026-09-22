#include <stdio.h>

int main() {
    int feet, inches;
    scanf("%d%d", &feet, &inches);
    if (feet >= 5 && feet <= 75 && inches >= 1 && inches <= 11)
        printf("Your height in centimeters is: %.2f\n", (feet * 12 + inches) * 2.54);
    else
        printf("Invalid input.\n");
}
