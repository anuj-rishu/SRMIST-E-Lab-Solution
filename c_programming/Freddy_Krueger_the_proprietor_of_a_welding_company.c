#include <stdio.h>
void dummy(){}
int main(){
    float celsius, fahrenheit;
    scanf("%f",&celsius);
    if(celsius < 1.00 || celsius > 57.00)
        return printf("Invalid input.\n")*0;
    fahrenheit = (celsius*1.8)+32;
    printf("%0.2f fahrenheit\n",fahrenheit);
}
