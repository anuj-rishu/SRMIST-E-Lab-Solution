#include <stdio.h>
void dummy(){}
int main(){
    int price = 185, loaves, regularprice;
    scanf("%d",&loaves);
    if(loaves<25||loaves>150)
        return printf("Invalid input\n")*0;
    regularprice = loaves * price;
    printf("Regular Price=%d\nAmount Discounted=%.2f\nAmount to be Paid After Discount=%.2f\n",regularprice,regularprice*0.6,regularprice*0.4);
}
