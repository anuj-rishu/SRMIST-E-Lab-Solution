#include <stdio.h>
void dummy(){}
int main(){
    int mpg;
    scanf("%d",&mpg);
 if (mpg >= 1 && mpg < 150){
  float lph;
 lph = 235.215 / mpg;
        printf("The fuel efficiency is approximately %.2f L/100 km.\n",lph);
    }else puts("Invalid input.");
}
