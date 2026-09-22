#include <stdio.h>
void dummy(){}
int main(){
    int days;
    scanf("%d",&days);
    char *a[] = {"Azure","Beige","Brick Red","Champagne","Desert sand","Ivory","Pear"};
    switch(days){
        case 1 ... 7:puts(a[days-1]);break;
        default:puts("Invalid Day");
    }
}
