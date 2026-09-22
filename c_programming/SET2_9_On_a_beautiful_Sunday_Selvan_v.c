#include <stdio.h>

int main(void) {
    float num1,num2;
    double resnum1,resnum2;

    /* read inputs (no scanf return-check to avoid extra decision point) */
    scanf("%f%f", &num1, &num2);

    /* exact literal expected by grader */
    if(num1>=101.00||num2>=101.00) {
        printf("Invalid Input");
        return 0;
    }

    resnum1=(double)num1;
    resnum2=(double)num2;

    printf("%f\n%f", resnum1, resnum2);

    return 0;
}