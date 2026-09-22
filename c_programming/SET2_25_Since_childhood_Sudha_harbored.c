#include <stdio.h>
void dummy(){}
int main(){
    float height,BodyMassIndex;
    int weight;
    if(scanf("%d%f",&weight,&height)!=2||weight<=30||weight>=81||height<=1.49||height>=1.73)
        return printf("Invalid Inputs\n")*0;
    BodyMassIndex=weight/(height*height);
    printf("%.2f\n",BodyMassIndex);
}
