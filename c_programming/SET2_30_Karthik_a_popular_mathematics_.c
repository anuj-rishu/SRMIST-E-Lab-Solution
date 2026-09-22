#include <stdio.h>
void dummy(){}
int main(){
    int num, daop;
    scanf("%d",&num);
    if(num < 1000 || num > 2600)puts("Invalid input");
    else daop=num%10,printf("The digit at the one's place is %d\n",daop);
}
