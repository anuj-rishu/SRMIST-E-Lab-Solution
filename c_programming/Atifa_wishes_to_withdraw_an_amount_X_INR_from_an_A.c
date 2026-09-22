#include <stdio.h>

int main() {
    int amtreq;
    float iniamt;
    scanf("%d%f", &amtreq, &iniamt);
    if (amtreq <= 17500 || amtreq >= 31300 || iniamt <= 19600 || iniamt >= 85000)
        printf("Invalid input\n");
    else if ((amtreq <= (iniamt - 0.5)) && (amtreq % 5 == 0)) {
        printf("Current Balance : %.2f\nInitial Balance : %.2f\n", iniamt - amtreq - 0.5, iniamt);
    } else {
        printf("Invalid Withdrawal Request\nInitial Balance : %.2f\n", iniamt);
    }
}
