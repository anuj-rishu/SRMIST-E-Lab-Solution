#include <stdio.h>
#include <math.h>
void dummy(){}
int main(){
    float gravity = 9.8, distance, vf;
    scanf("%f",&distance);
    if (distance >= 24.00 && distance <= 90.00){
        vf=sqrt(2*distance*gravity);
        printf("%.2f m/s\n",vf);
    }else printf("Invalid input\n");
}
