#include <stdio.h>
void dummy(){}
int main(){
    int workalloid;
    scanf("%d",&workalloid);
    char *j[] = {"Cinematographer","Editor","Marketing Manager","Content Engineer","Editorial Assistant"};
    switch(workalloid){
        case 101 ... 501:puts(j[workalloid/100-1]);break;
    }
}
