#include <stdio.h>

int main() {
    float length, width;
    scanf("%f%f", &length, &width);
    if (length >= 20.0 && length <= 100.0 && width >= 20.0 && width <= 100.0)
        printf("%.2f sq.ft\n", length * width);
    else
        printf("Invalid Input\n");
}
