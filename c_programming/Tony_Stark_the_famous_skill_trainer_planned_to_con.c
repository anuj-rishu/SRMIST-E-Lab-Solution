#include <stdio.h>
void dummy(){}
int main(){
    char operator;
    double n1, n2;
    if(scanf(" %c %lf %lf",&operator,&n1,&n2)!=3||n1<1||n1>500||n2<1||n2>500)
        return puts("Invalid input.")*0;
    switch(operator){
        case '+':printf("%.1f\n",n1+n2);break;
        case '-':printf("%.1f\n",n1-n2);break;
        case '*':printf("%.1f\n",n1*n2);break;
        case '/':printf("%.1f\n",n1/n2);break;
    }
}
