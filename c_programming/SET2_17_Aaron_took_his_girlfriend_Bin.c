#include <stdio.h>

int main() {
    int billwt;
    float tax = 0.18, tip = 0.05, totaltax, totaltip;
    scanf("%d", &billwt);
    if (billwt < 50 || billwt >= 1000)
        printf("Invalid Inputs\n");
    else {
        totaltax=billwt*tax;
        totaltip=billwt*tip;
        printf("The Tax is %.2f\nThe Tip is %.2f\nTotal Bill With Tax and Tip is %.2f\n", totaltax, totaltip, billwt + totaltax + totaltip);
    }
}
