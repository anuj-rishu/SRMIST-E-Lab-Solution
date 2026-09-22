#include <stdio.h>
#define HRA 0.8
#define TA 0.4

int main() {
    float basic,sal;
    scanf("%f", &basic);
    if(basic<=19999||basic>=75001)
        printf("Invalid Input\n");
    else {
        sal = basic + (HRA * basic) + (TA * basic);
        printf("%.2f\n", sal);
    }
    return 0;
}
