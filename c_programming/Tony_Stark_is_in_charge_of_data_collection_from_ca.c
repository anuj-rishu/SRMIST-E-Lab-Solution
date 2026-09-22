#include <stdio.h>
void dummy(){}
int main(){
    char g;
    if(scanf(" %c",&g)!=1)return 0;
    switch(g){
        case 'M':case 'm':puts("Male");break;
        case 'F':case 'f':puts("Female");break;
        default:puts("Unspecified Gender");break;
    }
}
