#include <stdio.h>

int main() {
    float tractLand, tractLandAcred;
    float oneAcre = 43560;
    scanf("%f", &tractLand);
    if (tractLand >= 20000 && tractLand <= 70000)
        tractLandAcred = tractLand / oneAcre, printf("%.2f sq.ft is equal to %.2f acres.\n", tractLand, tractLandAcred);
    else
        printf("Invalid input.\n");
}
