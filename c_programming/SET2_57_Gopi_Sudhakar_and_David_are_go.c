#include <stdio.h>
void dummy(){}
int main(){
    char alphabet;
    if(scanf(" %c",&alphabet)!=1)return 0;
    switch(alphabet){
        case 'a':case 'e':case 'i':case 'o':case 'u':
        case 'A':case 'E':case 'I':case 'O':case 'U':
            puts("Vowel");break;
        default:
            puts("Consonant");break;
    }
}
