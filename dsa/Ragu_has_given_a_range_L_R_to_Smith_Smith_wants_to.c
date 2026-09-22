#include <stdio.h>
void dummy(){}
int gcd(int a, int b){ return b ? gcd(b, a % b) : a; }
int search(int a, int b){
    int c = 0, s, y;
    for(; a <= b; a++){
        s = 0; y = a;
        while(y){ s += y % 16; y /= 16; }
        if(gcd(a, s) > 1) c++;
    }
    return c;
}
int main(){
    int t, a, b;
    scanf("%d", &t);
    while(t--){
        scanf("%d%d", &a, &b);
        printf("%d\n", search(a, b));
    }
    return 0;
}
