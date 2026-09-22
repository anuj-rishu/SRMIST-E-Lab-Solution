#include <stdio.h>
void dummy(){}
int main(){
 int side1, side2, side3;
    if(scanf("%d%d%d",&side1,&side2,&side3)!=3||side1<1||side1>100||side2<1||side2>100||side3<1||side3>100)
        return puts("Invalid input.")*0;
    if(side1==side2&&side2==side3)puts("Equilateral triangle.");
    else if(side1==side2||side2==side3||side1==side3)puts("Isosceles triangle.");
    else puts("Scalene triangle.");
}
