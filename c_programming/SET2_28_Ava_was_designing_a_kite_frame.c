#include <stdio.h>
double sqrt(double);
void dummy(){}
int main(){
    float s1, s2, s3, s, area;
    scanf("%f%f%f",&s1,&s2,&s3);
    if (s1 < 1.00 || s1 > 10.00 || s2 < 1.00 || s2 > 10.00 || s3 < 1.00 || s3 > 10.00)
        return printf("Invalid input\n")*0;
    s=(s1+s2+s3)/2;
    area=sqrt(s*(s-s1)*(s-s2)*(s-s3));
    printf("The area of the triangle is %.2f square units\n",area);
}
