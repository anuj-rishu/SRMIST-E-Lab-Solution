#include <stdio.h>

int main() {
    float radiusofball,volumeofball;
    scanf("%f",&radiusofball);
    if(radiusofball<=0.0 || radiusofball>=6.0) {
        printf("Invalid Input\n");
    } else {
         volumeofball = (4.0/3.0)*3.14*radiusofball*radiusofball*radiusofball;
        printf("%.2f\n", volumeofball);
    }
    return 0;
}
